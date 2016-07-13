CREATE TABLE `autobroadcast` (
  `id` INT(11) NOT NULL,
  `text` LONGTEXT NOT NULL,
  `next` INT(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;

INSERT  INTO `autobroadcast`(`id`,`text`,`next`) VALUES
(0,'last nextid',1),
(1,'AutoBroadcast - testovaci zprava 1, nasleduje 2.',2),
(2,'AutoBroadcast - testovaci zprava 2, nasleduje 3.',3),
(3,'AutoBroadcast - testovaci zprava 3, nasleduje 4.',4),
(4,'AutoBroadcast - testovaci zprava 4, nasleduje 5.',5),
(5,'AutoBroadcast - testovaci zprava 5, nasleduje 1.',1);

INSERT INTO `mangos_string`(`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`) VALUES
(1300,'|cff0000ee[Server Message]: |cffcc00ff%s|r',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);