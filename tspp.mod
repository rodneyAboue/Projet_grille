// Adaptation du TSP de OPL à un TSPP
// modifs tag LAURENT

// Cities

float alpha = ...; // weight on length
int     n       = ...;
range   Cities  = 1..n;

// Edges -- sparse set
tuple       edge        {int i; int j;}
setof(edge) Edges       = ...;
setof(int) CoveredBy[Cities] = ...;

//tuple Subtour { int size; int subtour[Cities]; }
//{Subtour} subtours = ...;

//int         dist[Edges] = ...;
// unitary distance on edges

// Decision variables
dvar boolean x[Edges]; // is edge e in tour ?
dvar boolean y[Cities]; // is node i visited ?
dvar boolean z[Cities]; // is node i covered ?

dvar int tourlength;
dvar int covered;

tuple Subtour { int size; int subtour[Cities]; }
{Subtour} subtours = ...;



/*****************************************************************************
 *
 * MODEL
 * 
 *****************************************************************************/

// Objective
// unitary distance on edges
minimize alpha*tourlength + (1.0 - alpha)*(n - covered);
subject to {

    tourlength == sum (<i,j> in Edges) 1.0*x[<i,j>];
    covered == sum(i in Cities) z[i];
   
   // Each city is linked with two other cities == 2yi // LAURENT
   forall (j in Cities : j != 1)
        sum (<i,j> in Edges) x[<i,j>] + sum (<j,k> in Edges) x[<j,k>] == 2*y[j];
        
   forall (s in subtours) 
	forall(i in Cities : s.subtour[i] == 1) 
		sum (<k, j> in Edges : 
			((s.subtour[k] == 1) && (s.subtour[j] == 0)) || 
			((s.subtour[k] == 0) && (s.subtour[j] == 1))
		) x[<j,j>] 
		>= 2*y[i];

   forall (j in Cities)
	z[j] <= (sum (i in CoveredBy[j]) y[i]); 
          
};

// POST-PROCESSING to find the subtours // PAS de sous tournées contenant 1

// Solution information
int thisSubtour[Cities];
int newSubtourSize;
int newSubtour[Cities];

// Auxiliary information
int visited[i in Cities] = 0;
setof(int) adj[j in Cities] = {i | <i,j> in Edges : x[<i,j>] == 1} union
                              {k | <j,k> in Edges : x[<j,k>] == 1};
execute {

  newSubtourSize = n;
  for (var i in Cities) { // Find an unexplored node
    if (visited[i]==1) continue;
    var start = i;
    var node = i;
    var thisSubtourSize = 0;
    for (var j in Cities)
      thisSubtour[j] = 0;
    while (node!=start || thisSubtourSize==0) {
      visited[node] = 1;
      var succ = start; 
      for (i in adj[node]) 
        if (visited[i] == 0) {
          succ = i;
          break;
        }
                        
      thisSubtour[node] = succ;
      node = succ;
      ++thisSubtourSize;
    }
    if (visited[1] == 1) continue; // Ajout LAURENT: pas de sous-tournée contenant le sommet de depart à éliminer

    writeln("Found subtour of size : ", thisSubtourSize);
    if (thisSubtourSize < newSubtourSize) {
      for (i in Cities)
        newSubtour[i] = thisSubtour[i];
        newSubtourSize = thisSubtourSize;
    }
  }
  if (newSubtourSize != n)
    writeln("Best subtour of size ", newSubtourSize);
}



/*****************************************************************************
 *
 * SCRIPT
 * 
 *****************************************************************************/

main {
	var opl = thisOplModel
		var mod = opl.modelDefinition;
	var dat = opl.dataElements;
	var bestobj = -1.0;
	var besttoursize;
	var curobj;
	var cit; 
	var cov;
	var sortie = "solutions.res";
        var res = new IloOplOutputFile(sortie);

	var status = 0;
	var it =0;
	while (dat.alpha < 1) {
		var cplex1 = new IloCplex();
		opl = new IloOplModel(mod,cplex1);
		opl.addDataSource(dat);
		opl.generate();
		it++;
		writeln("Iteration ",it, " with ", opl.subtours.size, " subtours.");
		if (!cplex1.solve()) {
			writeln("ERROR: could not solve");
			status = 1;
			opl.end();
			break;
		}
		opl.postProcess();
		curobj = cplex1.getObjValue();
		if ((curobj < bestobj) || (bestobj < 0)) bestobj = curobj;
		writeln("Current solution : ", curobj);

		if (opl.newSubtourSize == opl.n) {
			writeln("with alpha = ", opl.alpha, " best = ", bestobj, "Pareto point: ", opl.tourlength, " ", opl.n - opl.covered); 
			for(var v in opl.Cities) if (opl.y[v] == 1) write(v, " ");
			// Write file for Victor
			cit = 0;
			cov = 0;
			for(var v in opl.Cities) if (opl.y[v] == 1) cit++;
			cov = opl.covered;
			res.write(cit, " ", opl.tourlength, " "); // you can retrive tourlength
			for(var v in opl.Cities) if (opl.y[v] == 1) res.write(v, " ");
			res.write(cov, " ");	
			for(var v in opl.Cities) if (opl.z[v] == 1) res.write(v, " ");
			res.writeln();
			
			writeln();
			//writeln(" x = ", opl.x); 
			//writeln(" tour = ", opl.y); 
			//writeln(" viewed = ", opl.z); 
			dat.alpha = opl.alpha + 0.05;
			opl.end();
			cplex1.end();
			// break; // not found
		} else {

			// ajout de la tournée trouvée aux tournées
			dat.subtours.add(opl.newSubtourSize, opl.newSubtour);
			opl.end();
			cplex1.end();
		}
	}
	res.close();
	status;
}

