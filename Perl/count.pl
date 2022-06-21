#!/usr/bin/perl

use v5.10;
use warnings;
use strict;

my $oCounter = 0;
my $char;

while ( <STDIN> )
{
    foreach $char ( split(//, $_) )
    {
        if( $char eq "O" ){
            $oCounter++;
        }
    }
}

print "$oCounter\n";