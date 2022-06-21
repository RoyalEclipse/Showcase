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
my $name;
my $nameLoopCnt = 0;

NAMELOOP:
    foreach( @ARGV )
    {
        if( $_ =~ /^[[:alpha:]][[:alnum:]]*$/ )
        {
            $name = $_;
            # $name .="\n";
            # print "found name: $_!\n";
            undef $ARGV[$nameLoopCnt];
            last NAMELOOP;
        }
        $nameLoopCnt++;
    }

unless( defined $ARGV[0] ){
        $isARGV = 0;
    }

if( $isARGV )
{
READLOOP:
    foreach( @ARGV )
    {
        unless (defined $_ )
        {
            next READLOOP;
        }
        unless( open($FILE, "<", $_) )
        {
            close $FILE;
            print "cannot open file $_\n";
            print "in case it is a name please use only alnum chars with a letter at the beginning\n";
            next READLOOP;
        }
        while( <$FILE> )
        {
            if(defined $name)
            {
                $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
                $_ =~ s/(.*)\n/$1/;
                # print "reading $_ and looking for $name\n";
                # my $result = ($_ eq $name);
                # print $result;
                if( $_ eq $name )
                {
                    print "$_\n";
                    $lineCnt++;
                }
            }
            else
            {
            print "$_";
            $lineCnt++;
            }
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