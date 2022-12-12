# Compilation

In order to compile the code, you must run `make all`.

# Running

In order to run it, you must run `make run` or `./exe`.

## How to test it

Here we are treating categorical syllogisms, which means that each one will have 2 premises and a conclusion. Every one of these propositions have the structure "All/Some S are/are not P", with 'S' being the subject and 'P' the predicate. To be more general, the code also accept "all" and "some", and accept sentences ending with '.' and ','. Every time you give 3 categorical propositions - sentences with the structure above - the code will treat the first 2 as premises and the last one as the conclusion. Then, the code will process the syllogism and tell if it is valid ("Valid syllogism") or invalid ("Invalid syllogism"), using an algorithm based on a Venn's diagram.
