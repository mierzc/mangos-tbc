DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409007'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409003'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409004'; 
-- DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409007'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409008'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409009'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409010'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409011'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409012'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409020'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409021'; 
DELETE FROM `live_mangos`.`script_texts` WHERE `entry` = '-1409023'; 
INSERT INTO script_texts (entry,content_default,sound,TYPE,LANGUAGE,emote,COMMENT) VALUES 
-- (-1409007,'Impossible! Stay your attack, mortals... I submit! I submit! Brashly, you have come to wrest the secrets of the Living Flame! You will soon regret the recklessness of your quest. I go now to summon the lord whose house this is. Should you seek an audience with him, your paltry lives will surely be forfeit! Nevertheless, seek out his lair, if you dare!',8038,1,0,0,'majordomo SAY_DEFEAT_1'),
(-1409003,'Reckless mortals! None may challenge the Sons of the Living flame!',8035,1,0,0,'majordomo SAY_AGGRO'),
(-1409004,'The runes of warding have been destroyed! Hunt down the infidels, my brethren!',8039,6,0,0,'majordomo SAY_SPAWN'),
(-1409007,'Impossible! Stay your attack, mortals... I submit! I submit!',8038,1,0,0,'majordomo SAY_DEFEAT_1'),
(-1409008,'Behold Ragnaros - the Firelord! He who was ancient when this world was young! Bow before him, mortals! Bow before your ending!',8040,1,0,0,'ragnaros SAY_SUMMON_MAJ'),
(-1409009,'TOO SOON! YOU HAVE AWAKENED ME TOO SOON, EXECUTUS! WHAT IS THE MEANING OF THIS INTRUSION???',8043,1,0,0,'ragnaros SAY_ARRIVAL1_RAG'),
(-1409010,'These mortal infidels, my lord! They have invaded your sanctum and seek to steal your secrets!',8041,1,0,0,'ragnaros SAY_ARRIVAL2_MAJ'),
(-1409011,'FOOL! YOU ALLOWED THESE INSECTS TO RUN RAMPANT THROUGH THE HALLOWED CORE? AND NOW YOU LEAD THEM TO MY VERY LAIR? YOU HAVE FAILED ME, EXECUTUS! JUSTICE SHALL BE MET, INDEED!',8044,1,0,0,'ragnaros SAY_ARRIVAL3_RAG'),
(-1409012,'NOW FOR YOU, INSECTS! BOLDLY, YOU SOUGHT THE POWER OF RAGNAROS. NOW YOU SHALL SEE IT FIRSTHAND!',8045,1,0,0,'ragnaros SAY_ARRIVAL5_RAG'),
(-1409020,'Brashly, you have come to wrest the secrets of the Living Flame! You will soon regret the recklessness of your quest.',0,1,0,0,'majordomo SAY_DEFEAT_2'),
(-1409021,'I go now to summon the lord whose house this is. Should you seek an audience with him, your paltry lives will surely be forfeit! Nevertheless, seek out his lair, if you dare!',0,1,0,0,'majordomo SAY_DEFEAT_3'),
(-1409023,'Very well, $n.',0,0,0,0,'majordomo SAY_SUMMON_0');