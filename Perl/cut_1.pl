#!/usr/bin/perl -anF:

use v5.10;
use warnings;
use strict;

BEGIN{

    unless( defined $ARGV[0] ){
        print "Header of the list: usernames in STDIN\n";
    }
    else{
    print "Header of the list: usernames in ";
    for ( @ARGV )
    {
        print "$_ ";
    }
    print "\n";
    }

    my $colnum=$ENV{COLUMNS};
    unless( defined $colnum ){
        $colnum=80;
    }
    my $lineseparator="=";
    
    while ( $colnum > 1 )
    {
        $lineseparator="$lineseparator=";
        $colnum--;
    }
    
    $lineseparator="$lineseparator\n";
    print $lineseparator;

    my $linestotal=0;
}

print "$F[0]\n";

END{
    my $colnum=$ENV{COLUMNS};
    unless( defined $colnum ){
        $colnum=80;
    }
    my $lineseparator="=";
    
    while ( $colnum > 1 )
    {
        $lineseparator="$lineseparator=";
        $colnum--;
    }
    
    $lineseparator="$lineseparator\n";
    print $lineseparator;

    print "Footer of the list: lines=$.\n"

}