#!/usr/bin/perl

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

# TODO
my $FILE;
my $lineCnt = 0;
my $curline;
my $isARGV = 1;
unless( defined $ARGV[0] ){
        $isARGV = 0;
    }

if( $isARGV )
{
    foreach( @ARGV )
    {
        unless( open($FILE, "<", $_) )
        {
            close $FILE;
            die "cannot open file $_";
        }
        while( <$FILE> )
        {
            $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
            print "$_";
            $lineCnt++;
        }
    
        close($FILE);
    }
}
else
{
    while( <> )
    {
        $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
            print "$_";
            $lineCnt++;
    }
    
}

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

    print "Footer of the list: lines=$lineCnt\n"

}