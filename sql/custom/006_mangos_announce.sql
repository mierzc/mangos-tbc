-- mangos_string Announce 
REPLACE INTO `mangos_string` VALUES
(3, '|cFFff0000[Mysteria Message]|cff00ff00<GM>|cffff9900%s: |cffffff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(4, '|cFFff0000[Mysteria Message]|cff00ff00<GM>|cffffff00%s: |cffff6600%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11000, '|cffff0000[Console Message]: |cff00ff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11001, '|cFFff0000[Mysteria Message]|cff00ff00<Admin>|cffff9900%s: |cffffff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11002, '|cFFff0000[Mysteria Message]|cff00ff00<Eventer>|cffff9900%s: |cffffff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11011, '|cFFff0000[Mysteria Message]|cff00ff00<Moderator>|cffff9900%s: |cffffff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(11012, '|cFFff0000[Mysteria Message]|cff00ff00<Developer>|cffff9900%s: |cffffff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- .pinfo zobrazuje aj guildu
UPDATE `mangos_string` SET `content_default`='Player%s %s (guid: %u) Account: %s (id: %u) GMLevel: %u Guild: <%s> Last IP: %s Last login: %s Latency: %ums' WHERE `entry`='548' ;
