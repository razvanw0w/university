use GamesRental;

-- Drumul Taberei Street got demolished.
-- we can rule all clients who lived on Drumul Taberei out.
delete from clients
where address like 'Drumul Taberei%';

-- NDS and GameBoy are deprecated platforms
-- we can eliminate them
delete from platforms
where name in ('NDS', 'GameBoy')