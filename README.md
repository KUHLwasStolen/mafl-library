# mafl-library
Useful command line tools for people interested in mathematics and computer science (with a focus on the latter).  

~~~
           /////////////////////////////////////////////////////////////////////////////////
          ///      /////      ////////////     ////////////             ///   /////////////
         ///   /   ///   /   ///////////   /   ///////////   /////////////   /////////////
        ///   //   /   //   //////////   ///   //////////   /////////////   /////////////
       ///   ///     ///   /////////   /////   /////////   /////////////   /////////////
      ///   ////   ////   ////////   ///////   ////////             ///   /////////////
     ///   ///////////   ///////   /////////   ///////   /////////////   /////////////
    ///   ///////////   //////                 //////   /////////////   /////////////
   ///   ///////////   /////   /////////////   /////   /////////////   /////////////
  ///   ///////////   ////   ///////////////   ////   /////////////   /////////////
 ///   ///////////   ///   /////////////////   ///   /////////////             ///
/////////////////////////////////////////////////////////////////////////////////
~~~

1. [About](#about)
2. [Features](#features)  
2.1 [Mathematics](#mathematics)  
2.2 [Computer Science](#computer-science)
3. [Usage](#usage)

*Note:* As of now the output of `mafl -h` claims things that the project cannot YET do, as this is a very early stage.  

## About

`mafl` stands for '**MA**ths' and '**A**utomata, **F**ormal **L**anguages and computation'.  
The project's aim is to implement everything I learned/learn at university about these two subjects and make it available in an open and easy-to-use library.  
This does not mean that the project will be limited to this, but the basic idea is as stated above.  

I am well aware that this is probably not the first tool for the terminal that provides this functionality. But this is mine and it serves more of an educational purpose than anything else.  
Furthermore this project is also about practicing my current programming skills, not about finding the very best method of doing something.  
*Of course contributions and all sorts of improvements or recommendations are still very welcome, this was just to clarify that this project is not about doing stuff 'THE easy way', but rather about figuring A way.*

Now that the scope of the project is clear let's dig into the details.

## Features

### Mathematics

none at the moment :(  

### Computer Science

**DFA** *(Deterministic Finite Automaton)*  
- Reads a DFA either from the command line or a previously stored file (WIP atm) and then let's you test its functionality
- Stores configuration files for automata that you have created in the command line

## Usage

Of course before you can use it, you need an executable file on your system. To get this I recommend downloading the source code from the `trunk` branch and then compiling it (with gcc) in its folder like this:
~~~
gcc *.c -o mafl
~~~
*(gcc is recommended as the code gets tested with it, I cannot promise compatibility with other compilers)*

Move your compiled file to a folder that's included in your PATH variable and now you're ready to use it anywhere!  

It basically works like any other command line tool:  
Type `mafl --help` or `mafl -h` to get a detailed list of everything that the tool can do or type `mafl -?` to get a shorter version of this without explanations.  

&nbsp;  

And last but not least: have fun with your new tool!  
If you have questions/problems feel free to open a new issue.
