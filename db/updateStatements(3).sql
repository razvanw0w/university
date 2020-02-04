use GamesRental;

-- some of the composers weren't rated yet so they will receive a default rating
update composers
set rating = 50
where rating IS NULL;

-- a composer is retiring, thus, he will not compose soundtracks for games anymore
-- all his work will be passed to his son (except FIFA Madness 5, his favourite game), a new composer on his road to glory
update isComposed
set composerID = 30
where composerID = 1 AND gameID != 60;

-- smaller publishers are encouraged to do more games
-- if their revenue is between 15 and 25 mil $ they receive a bonus up to 25 mil $ revenue
update publishers
set revenue = 25
where revenue between 15 and 25;

-- C is now not that used in programming games so the C programmers need to
-- adjust to the trends
update programmers
set programmingLanguage = 'C#'
where programmingLanguage = 'C' or programmingLanguage = 'C++';