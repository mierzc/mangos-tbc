-- Freeze prikazy
DELETE FROM `command` WHERE `name` = 'freeze' or `name` = 'unfreeze' or name = 'listfreeze';
INSERT INTO `command` (`name`,`security`,`help`) VALUES 
('freeze','3','Syntax: .freeze (#player)\r\n\"Freezes\" #player. When using this without #name it will freeze your target.'),
('unfreeze','3','Syntax: .unfreeze (#player)\r\n\"Unfreezes\" #player. When using this without #name it will unfrezze your target.'),
('listfreeze','3','Syntax: .listfreeze\r\n\r\nSearch and output all frozen players.');

-- mangos_string definicie	
DELETE FROM mangos_string WHERE entry BETWEEN 10900 AND 10906;
INSERT INTO mangos_string VALUES
(10900,'Zmrazil si hraca %s.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10901,'Nemozes zmrazit sam seba!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10902,'Invalid input #name or target.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10903,'Odmrazil si hraca %s.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10904,'Niesu tu ziadni zmrazeni hraci.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10905,'Nasledujuci hraci su stale zmrazeni;',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(10906,'- %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

-- BG prikazy
REPLACE INTO `command` (`name`, `security`, `help`) VALUES
('wsg', '0', 'Syntax: .wsg Prihlasi do Warsong Gulch'),
('ab',  '0', 'Syntax: .wsg Prihlasi do Arathi Basin'),
('av',  '0', 'Syntax: .wsg Prihlasi do Alterac Valley'),
('eos', '0', 'Syntax: .wsg Prihlasi do Eye Of The Storm');
