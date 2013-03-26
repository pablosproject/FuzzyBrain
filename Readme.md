FuzzyBrain
============
Introduction
------------
FuzzyBrain is a fuzzy logic inference engine completely written in C++. It is designed to be simple to use,extend and to be fast! You can take the code in the */src* directory ad add to your project.

Every single variable and fuzzy set in the system can be configured manually, and you can fire the inference as many time you want.

##Usage
Conceptually there are several elements that play different roles in the fuzzy inference system.

|Component|Role|
|---------|----|
|FuzzySet|Represent a single fuzzy set in a linguistic variable|
|Linguistic variable| Fuzzy logic linguistic variable that contain fuzzy sets|
|FuzzyRule|Single fuzzy rule written in natural language|
|FuzzyObject|Single unit of fuzzy inference, contain linguistic variables and rules|
|Defuzzificators|Objects that defuzzify an output variable|
|FuzzyEngine|Container of several FuzzyObject|

Let's make an example using code: a fuzzy calculator.
'''C++
     //First: creation of the fuzzy object
     calculator = new MamdaniFuzzyObject();

     /*
     *  Creation of the linguistic variables for input and output
     */
      InputLinguisticVariable* x = new InputLinguisticVariable("x",-10,10);
      TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
      TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
      TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);
      //Add set to variable x
      x->addSet(negative);
      x->addSet(zero);
      x->addSet(positive);

      MamdaniOutputVariable* y = new MamdaniOutputVariable("y", -3,3);
      TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
      TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
      TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
      TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);



      y->addSet(negative_2);
      y->addSet(zero);
      y->addSet(positive_2);
      y->addSet(largenegative);
      y->addSet(largepositive);

      InputLinguisticVariable* z = new InputLinguisticVariable("z", -10, 10);

      z->addSet(negative);
      z->addSet(zero);
      z->addSet(positive);

      calculator->addInputVar(x);
      calculator->setOutputVar(y);
      calculator->addInputVar(z);

      /*
      * Adding a series of rules
      */
      calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
      calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
      calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
      calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
      calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
      calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
      calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
      calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
      calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));

      /*
      * Set input for the variables
      */
      calculator->setInput("z",1);
  
      /*
      * Fire the inference and get an output
      */

      float output = calculator->getOutput();


'''


This is a base case using only one FuzzyObject. If needed a FuzzyEngine can be used to collect several fuzzy object, manage relationship between objects and manage input and output. Also you can provide an EngineCreator that permit to import the engine from an XML or other sources.


##Documentation
All the documentation for the source code can be found at http://fuzzybrain.pablosproject.com/.

#Contact

You can contact me for every question at pablosproject@gmail.com or twitter @PablosProject.