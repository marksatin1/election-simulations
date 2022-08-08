# README

A plurality election is successful if one candidate has the majority of the vote, but if two or more candidates split the vote there is no logic involved to break the tie.

In a runoff election voters rank candidates from their first to last choice. The candidate with a >50% majority wins. In the event of a tie, the candidate with the least amount of votes is eliminated and all voters who voted for the eliminated candidate have their second choice considered. If this give the majority to one of the remaining candidates, then that candidate wins. If another tie ensues then the next candidate with the least amount of votes is eliminated and all votes for that person are redistributed to the remaining candidates. The process repeats until someone is selected.

It is possible for a tie to occur between two or more candidates, but it is less likely. While not perfect, a runoff election is more likely to lead to the election of a candidate that best reflects voters' choices.

**Note:** Some runoff elections don't require voters to rank every candidate but runoff.c assumes that all voters will rank all candidates on their ballot.

The struct 'candidate' contains a person's name, the number of votes they received, and their elimination status. The ''candidates array contains all of these candidates.

runoff.c takes between two and nine candidate names as arguments. Any more or less will throw an error. The module first prompts the user for the number of voters in the simulation which is maxed out at 100. Any more will throw an error as will entering a non-interger when prompted for votes.

The module then prompts the user to enter each voter's ranked votes.

tabulate() tallies the first-choice votes each candidate receives. If a candidate gains more than 50% of the vote, they win the election and their name is printed to the console. If not, the least amount of votes any candidate has is identified by find_min().

is_tie() ensures that every remaining candidate does not hold this minimum number of votes. If they do, then they split the vote and the election ends in a tie. If there is no tie, then the candidate(s) with the minimum amount of votes is eliminated and the entire process is run again. This repeats until a winner is found or a tie ensues.
  
  
#### EXAMPLE INPUT

./runoff Mark Ben  
Number of voters: 3  
VOTER 1  
Rank 1: Mark  
Rank 2: Ben  
  
VOTER 2  
Rank 1: Ben  
Rank 2: Mark  
  
VOTER 3  
Rank 1: Mark  
Rank 2: Ben  
  
  
#### EXAMPLE OUTPUT

Mark is the election winner!  
The election is tied.  
