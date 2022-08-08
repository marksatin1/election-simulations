# README

In a plurality election, the candidate with the most votes out of all possible votes wins.

plurality.c simulates such an election by prompting the user for candidate names on the command line. The user can submit between 2 and 9 names. Otherwise they will be hit with an error and the program will exit. The module then prompts the user to enter the number of people voting in the election. This number must be an integer or it will throw an error and exit.

The struct 'candidate' consists of a person's name and the number of votes attached to them. The 'candidates' array contains the list of all candidates in the simulation.

plurality.c will prompt the user with "Vote: " wherein the user enters the name of the candidate who was voted for. If the candidate name does not match an entry in the candidates array that vote will not be tallied and plurality.c will prompt the user to re-enter a candidate name for that same vote. After a successful candidate name is entered the module will prompt for the next vote. This continues until all votes have been tallied.

All votes are then counted and the winner is determined as is the percentage of votes they received to secure their victory. This information is printed to the command line.

#### EXAMPLE INPUT

./plurality Mark Ben  
Number of voters: 5  
Vote: Mark  
Vote: Mark  
Vote: Alex  
ERROR: This person is not running in the election.  
Vote: Ben  
Vote: Mark  
Vote: Ben  

#### EXAMPLE OUTPUT

Mark is the winner with 60 percent of the vote.  
