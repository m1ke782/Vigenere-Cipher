# Vigenere-Cipher

Some C program which uses Trigram Analysis as a loss function for a genetic mutation algorithm to solve Vignere ciphers.

# Basic Operating Principles

Here is the basic strategy to solving Vignere Ciphers. This code implements all steps marked with (*) :

1. Use frequency analysis to guess a key length.
2. (*) Generate a random key
3. (*) Use Trigram Analysis to generate a fitness value
4. (*) Make a random mutation to the key
5. (*) Use Trigram Analysis to generate a fitness value after the mutation
6. (*) If the key is more fit after the mutation, keep it. Otherwise, reverse the mutation.
7. (*) Repeat from step 2 for many iterations or until a stable key is found.
8. Check the key is accurate by inspecting the decoded messgage.
9. If not, repeat again, possibly changing starting key or key length.
