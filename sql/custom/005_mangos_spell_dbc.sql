-- Spell.dbc
CREATE TABLE `dbc_spell` (
  `SpellID` int(9) unsigned NOT NULL,
  `CastingTimeIndex` int(9) unsigned DEFAULT NULL,
  `DurationIndex` int(9) unsigned DEFAULT NULL,
  `EffectBasePoints0` int(9) DEFAULT NULL,
  `EffectBasePoints1` int(9) DEFAULT NULL,
  `EffectBasePoints2` int(9) DEFAULT NULL,
  `Comment` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`SpellID`),
  UNIQUE KEY `SpellID` (`SpellID`),
  KEY `SpellID_2` (`SpellID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

DELETE FROM `command` WHERE `name` = 'reload dbc';
REPLACE INTO `command` (`name`, `security`) VALUES ('reload dbc', '1') ;
REPLACE INTO `command` (`name`, `security`) VALUES ('reload creature_templatex', '1') ;


-- rozsirenie tabulky Spell.dbc
ALTER TABLE `dbc_spell` ADD `Attributes`    INT(11) UNSIGNED DEFAULT NULL NULL AFTER `EffectBasePoints2` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx`  INT(11) UNSIGNED DEFAULT NULL NULL AFTER `Attributes` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx2` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx3` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx2` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx4` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx3` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx5` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx4` ;
ALTER TABLE `dbc_spell` ADD `AttributesEx6` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx5` ;
ALTER TABLE `dbc_spell` ADD `Dispel` INT(11) UNSIGNED DEFAULT NULL NULL AFTER `AttributesEx6` ; 

REPLACE INTO `dbc_spell` (`SpellID`, `CastingTimeIndex`, `DurationIndex`, `EffectBasePoints0`, `EffectBasePoints1`, `EffectBasePoints2`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `Comment`) VALUES ('3600', NULL, NULL, NULL, NULL, NULL, NULL, '168', NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `dbc_spell` (`SpellID`, `CastingTimeIndex`, `DurationIndex`, `EffectBasePoints0`, `EffectBasePoints1`, `EffectBasePoints2`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `Comment`) VALUES ('29858', NULL, NULL, NULL, NULL, NULL, NULL, '1056', NULL, NULL, NULL, NULL, NULL, NULL);

-- DBC summon
CREATE TABLE `dbc_summonproperties` (
  `id` int(11) unsigned NOT NULL,
  `group_property` int(11) unsigned DEFAULT NULL,
  `faction` int(11) unsigned DEFAULT NULL,
  `type` int(11) unsigned DEFAULT NULL,
  `slot` int(11) unsigned DEFAULT NULL,
  `flags` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

INSERT INTO `dbc_summonproperties` (`id`, `group_property`, `faction`, `type`, `slot`, `flags`) VALUES ('407','1','0','5','5','0');
