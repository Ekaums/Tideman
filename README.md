# Tideman
This project implements the tideman voting system. The voting system is explained here: https://en.wikipedia.org/wiki/Ranked_pairs#:~:text=Ranked%20pairs%20(sometimes%20abbreviated%20%22RP,a%20sorted%20list%20of%20winners.

Essentially, this voting system is a ranked-preference voting system. This means that every voter, instead of voting for one candidate, will rank every candidate in order of preference.

Then, the system uses ranked pairs. This means it will look at every possible pair of candidates, and determine who would have won if the election was just between these two.

After these pairs are determined, we can visualize the results by listing every candidate, and drawing an arrow from the winner to the loser. This indicates which candidate would have beaten which in a head-to-head matchup.

Once we have all arrows (aka edges) drawn, the winner would be the "source" of the graph, or the candidate who has no arrows pointed to them, but does have arrows pointing at others.
