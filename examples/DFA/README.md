# DFA

## Contents

### Overview
In this chapter of our examples, we will cover everything you need to know about DFAs in mafl.  
*(DFA = **D**eterministic **F**inite **A**utomaton)*  
To illustrate everything that mafl can do with DFAs we will use an automaton which decides the Language $L_{1}$:  
$$L_{1} := \\{ a^{n*3} \hspace{3mm}|\hspace{3mm} n \in \mathbb{N}_{0} \\}$$  
Written out: All valid inputs are those who are made up of only a's and where the amount of a's is divisable by 3.  
This is achievable with a simple automaton with 3 states.  
A visual representation of the automaton would look like this:  

<img src="/examples/DFA/DFAexample01.png" alt="Drawing of DFAexample01" width="350"/>

Let's skip a formal definition and let's [enter it directly into the CLI](#from-the-terminal).  

&nbsp;  


1. [Reading DFAs](#reading-dfas)  
1.1 [From the terminal](#from-the-terminal)  
1.2 [From a file](#from-a-file)  
2. [Saving DFAs](#saving-dfas)  
3. [Testing DFAs](#testing-dfas)  
4. [Minimizing DFAs](#minimizing-dfas)  

## Reading DFAs

### From the terminal

To enter our DFA which we have laid out in the [Overview](#overview) we are going to use the simplest way of entering a DFA into `mafl`:  
Type: `mafl --dfa` or `mafl -dfa`  
No further options needed right now.  
The program will now start to ask the following things in this order:  
1. Set of states
2. Set of symbols
3. Transition function
4. Starting state
5. Accepting states

*(For the sake of demonstrating everything, I will mark user input with `>>>`, this will not show up on your screen)*  

**Step 1**  
~~~
Enter the set of states Q
Individual states sperated by a comma, spaces will be ignored, character limit: 250
>>> q0,q1,q2
~~~
Here we have entered the three states that we need for our automaton.  
We can call them however we like. I chose to use `q` for states and then enumerate up to infinity.  
This is not really recommended for more complicated automata, but this simple example is clear enough without using special names. 

**Step 2**  
~~~
3 states registered
Now enter the input alphabet
Same rules as for entering the states
>>> a
~~~
From our definition for $L_1$ we know that we only need one symbol, which is `a`.  
If we would need more symbols, let's say 'b' and 'c', then we would also seperate them like we did with the states above.  
Theoretically, it would also be possible to give the symbols multi-letter names like 'a1', 'a2', ...  
But this is a rather uncommon practice, so let's keep it simple and go back to our example.

**Step 3**  
~~~
1 symbol registered
Now enter the transition function d
Choose one of the following states for each transition and enter the corresponding number
States: 0 = q0, 1 = q1, 2 = q2
d(q0, a) = >>> 1
d(q1, a) = >>> 2
d(q2, a) = >>> 0
~~~
Now we tell the program how to behave for input in our states.  
`mafl` will walk you through all necessary transitions and you just have to enter the corresponding indices for the states that you want to enter.  
You could read the delta function as follows:  
`d(q0, a) = 1` = "When we read an `a` in state `q0` we go to state `1`, which corresponds to `q1` in our case.  

To further illustrate our example let me explain the transition function. We always want to loop around our states, as we always accept a's in a set of 3.  

In an automaton with more than one input symbol the program would run you through all the transitions for ***one*** state and ***all*** symbols and then move on to the next state and do the same again.

**Step 4**
~~~
Now enter the starting state
Choose one of the following states and enter the corresponding number
States: 0 = q0, 1 = q1, 2 = q2
>>> 0
~~~
Here we only need to enter one number, as a DFA can only have one starting state.  
Choose the right state for your automaton from the list and enter its number. In the case of the example `0`, which corresponds to `q0` (this is where this naming scheme for states starts to make sense).

**Step 5**  
~~~
Now enter the set of accepting states
Is 'q0' an accepting state? [y/n] >>> y
Is 'q1' an accepting state? [y/n] >>> n
Is 'q2' an accepting state? [y/n] >>> n
~~~
Now we just have to enter in which states we want to accept the input.  
For our example we do this as shown above.  

This last step concludes the manual entering of a DFA into `mafl`.  
If everything went right and if not specified differently, you will now enter the testing of you DFA, which is explained in detail [below](#testing-dfas).  

### From a file

A more convenient way to enter a DFA into `mafl` is to read it from a previously saved configuration file. This is especially useful if you want to reuse one specific automaton multiple times.  

How do we get such a file? This is covered in the [next section](#saving-dfas).  

If you already have a presaved config you can read it like this:  
~~~
mafl --dfa --read <file>
~~~
Alternatively like this:
~~~
mafl -dfa -r <file>
~~~
Or a combination of both.  

Let's try it out with our example from the beginning. If you don't have a file for this specific DFA yet, you can get it [here](/examples/DFA/DFAexample01.txt).  
We can load this specific file like this for example:
~~~
mafl --dfa -r DFAexample01.txt
~~~
*(This only applies if you are in the same directory of course, find your file with the help of `TAB` to be more sure)*  

If everything went right, you should now see the standard testing environment of `mafl`. If you are not familiar with it yet, it is described in detail [here](#testing-dfas).

## Saving DFAs

If you need a specific DFA more than once, you can save it for later by letting `mafl` create a configuration file for it.  
You need to decide if you want to save it before running the program. If you are unsure, whether you want to save it or not, saving it is the wiser option, as it doesn't take much storage and you can always delete it later.  

To save a DFA you basically have to options:  
~~~
mafl --dfa --save
~~~
This will save your automaton and give it a random name of this form: `savedDFA1234.txt`  
You should rename that file immediatly after it was generated, because **theoretically** it could be overwritten if the program randomly generated the same name again. There is a 1 : 10000 chance for this, but better safe than sorry.  

To avoid this altogether you can name your DFA from the beginning on:  
~~~
mafl -dfa -s --name <filename>
~~~
The automaton will be saved in a file according to your specification. Do not include any file extension here. The program will handle that for you.  
So for example if we run...
~~~
mafl -dfa -s -n awesomeDFA42
~~~
...a file with the name `awesomeDFA42.txt` will be created which contains all the necessary information to [read](#from-a-file) the automaton later.  

If you take a look into the file you will probably be able to understand most of the entries there.  
**Still**, I strongly advise against modifying your DFA by editing the text-file that was created. Do this on your own "risk", if you still want to try it.  
*(There is no real "risk", but the probability of it doing what you expected it to do is very low)*

## Testing DFAs

The testing mode for your DFA automatically starts after it was entered. No matter **how** it was entered.  

The program will tell you in which state the automaton currently is and whether this is an accepting state or not.  
You can enter the word you want to test symbol by symbol, which allows you to observe each step.  
At the beginning the program will also tell you the symbols you may use, which is great if you haven't used the DFA recently.  

To quit the testing mode, just type something that is not part of the input alphabet.  
If you set the `--save` when you started the program, do not exit the testing mode with `^C`. This will cause the program to halt immediatly and skip the saving step.  
Only do this, if you are unhappy with the behaviour of your automaton and you don't want to keep it.  

## Minimizing DFAs  

Hand-written automata are often created in a non-optimal way.  
Be it because the creator didn't notice a way to keep it more simple or (the more common reason) to make it more simple and easy to read.  
But using such automata in a 'real-life application' is inefficient and uses more system resources than needed.  
This section will cover how you can create a minimal automaton with `mafl`.  

Basically you just have to add the `--minimize` or `-m` flag to your program call. That's it.  
But let's cover it in a bit more detail.  
We will again use $L_1$ to demonstrate minimization. But now let's inflate the automaton for no good reason.  
Instead of 3 states, we will now use 9 states. The additional states just repeat the pattern that we have created before.  
I will now skip over explaining every single step and just show you what the terminal should look like.  
I called the program using `mafl -dfa -m -s -n minimalDFAexample01`

*(User input is again specified with `>>>` which will not show up on your screen)*
~~~
Enter the set of states Q
Individual states sperated by a comma, spaces will be ignored, character limit: 250
>>> q0,q1,q2,q3,q4,q5,q6,q7,q8

9 states registered
Now enter the input alphabet
Same rules as for entering the states
>>> a

1 symbol registered
Now enter the transition function d
Choose one of the following states for each transition and enter the corresponding number
States: 0 = q0, 1 = q1, 2 = q2, 3 = q3, 4 = q4, 5 = q5, 6 = q6, 7 = q7, 8 = q8
d(q0, a) = >>> 1
d(q1, a) = >>> 2
d(q2, a) = >>> 3
d(q3, a) = >>> 4
d(q4, a) = >>> 5
d(q5, a) = >>> 6
d(q6, a) = >>> 7
d(q7, a) = >>> 8
d(q8, a) = >>> 0

Now enter the starting state
Choose one of the following states and enter the corresponding number
States: 0 = q0, 1 = q1, 2 = q2, 3 = q3, 4 = q4, 5 = q5, 6 = q6, 7 = q7, 8 = q8
>>> 0

Now enter the set of accepting states
Is 'q0' an accepting state? [y/n] >>> y
Is 'q1' an accepting state? [y/n] >>> n
Is 'q2' an accepting state? [y/n] >>> n
Is 'q3' an accepting state? [y/n] >>> y
Is 'q4' an accepting state? [y/n] >>> n
Is 'q5' an accepting state? [y/n] >>> n
Is 'q6' an accepting state? [y/n] >>> y
Is 'q7' an accepting state? [y/n] >>> n
Is 'q8' an accepting state? [y/n] >>> n
~~~

I hope that entering the DFA is pretty self-explanatory. If not, go over [this section](#from-the-terminal) again.  
Alternatively you can get the DFA configuration [here](/examples/DFA/nonMinDFAexample01.txt) and enter it using `mafl -dfa -r nonMinDFAexample01.txt -m -s -n minimalDFAexample01`.  

Now let's go over the more important terminal output which I have hidden until now:  
~~~
Got rid of 6 states (9 --> 3)
The new states are:
'q0q3q6' (accepting, starting)
'q1q4q7'
'q2q5q8'

The new transition function:
d(q0q3q6, a) = q1q4q7
d(q1q4q7, a) = q2q5q8
d(q2q5q8, a) = q0q3q6

The automaton you will be testing is the minimal one.
~~~

The program will show you how your automaton was modified to make it minimal.  
After minimizing, `mafl` will entern [testing](#testing-dfas) mode. As stated above, you will be testing the minimal automaton, which should behave exactly like the one that was entered, but it has less states.  

You can find the specific minimal automaton, that we have created in this example [here](/examples/DFA/minimalDFAexample01.txt).  

**Note:** When you are saving a DFA and also minimizing it, only the minimal version will be saved.  
If you need your non-minimal automaton later, make sure to enter and save it, and then run `mafl` again and save your minimal automaton seperately.  

&nbsp;  

That's it! These are the basics of using DFAs in `mafl`.  
For further reference along the way you can consult one of the following options...
~~~
mafl --help
mafl -h
mafl -?
~~~
...or open a new issue if you can't figure something out on your own. We are always happy to help :)
