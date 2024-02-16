# DFA

## Contents

### Overview
In this chapter of our examples, we will cover everything you need to know about DFAs in mafl.  
*(DFA = **D**eterministic **F**inite **A**utomaton)*  
To illustrate everything that mafl can do with DFAs we will use an automaton which decides the Language $L_{1}$:  
$$L_{1} := \{a^{n*3} \hspace{3mm}|\hspace{3mm} n \in \N_{0}\}$$  
In spoken words: All valid inputs are those who are made up of only a's and where the amount of a's is divisable by 3.  
This is achievable with a simple automaton with 3 states. Let's skip a formal definition and let's [enter it directly into the CLI](#from-the-terminal).  

&nbsp;  


1. [Reading DFAs](#reading-dfas)  
1.1 [From the terminal](#from-the-terminal)  
1.2 [From a file](#from-a-file)  
2. [Saving DFAs](#saving-dfas)  
3. [Testing DFAs](#testing-dfas)  

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

A more convenient way to enter a DFA into `mafl` is to read it from a previously saved configuration file.

## Saving DFAs

## Testing DFAs