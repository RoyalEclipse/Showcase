#!/usr/bin/perl

use v5.10;
use warnings;
use strict;

open my $infile, "$ARGV[0]" or die "Could not open $ARGV[0]: $!";

my $xMax;
my $yMax;
my $xCurrent;
my $yCurrent;
my $actors ="";
my $noEnemies = 1;

while( my $line = <$infile>)
{
    my @characters = split(//, $line);
    $yCurrent++;
    $yMax++;
    if( $characters[0] eq '-' ){ $xMax = length($line); next; }

    $xCurrent = 0;
    foreach( @characters )
    {
        $xCurrent++;
        if( $_ eq '|' or $_ eq " " ){ next; }
        if( $_ eq 'O' ){ $actors = $actors."1 ".$xCurrent." ".$yCurrent." HP DMG SPD AXIS\n"; $noEnemies = 0; ; }
        if( $_ eq 'Z' ){ $actors = $actors."2 ".$xCurrent." ".$yCurrent." HP DMG SPD\n"; $noEnemies = 0; }
        if( $_ eq '#' ){ $actors = $actors."3 ".$xCurrent." ".$yCurrent."\n"; }
        if( $_ eq '?' ){ $actors = $actors."4 ".$xCurrent." ".$yCurrent."\n"; }

    }

}

$yMax++;
$yMax++;


print "0 ONMAPX ONMAPY $xMax $yMax DOORUP DOORDOWN DOORLEFT DOORRIGHT $noEnemies\n";
print "$actors"