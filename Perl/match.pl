#!/usr/bin/perl

use v5.10;
use warnings;
use strict;

BEGIN{

    unless( defined $ARGV[1] ){
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
my $wantUidSearch = 0;
unless( defined $ARGV[1] ){
        $isARGV = 0;
    }

if ( defined $ARGV[0] ){
    if( $ARGV[0] =~ /\d*/ ){
    $wantUidSearch = $ARGV[0];}
    else {
        $wantUidSearch = 0;
    }
}

if( $isARGV )
{
ASSEBLERISASS:
    foreach( @ARGV )
    {
        unless( open($FILE, "<", $_) )
        {
            # skip to next if curargv is uid to search
            if ( $_ =~ /\d*/ ){ next; }
            close $FILE;
            die "cannot open file $_";
        }
        while( <$FILE> )
        {   
            if( $wantUidSearch != 0 )
            {
                if( $_ =~ m/^[^:]*:[^:]*:$wantUidSearch:/ )
                {
                    $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
                    # print "sugma\n";
                    print "$_";
                    $lineCnt++;
                }
            }
            else{
                $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
                print "$_";
                $lineCnt++;
            }
        }
    
        close($FILE);
    }
}
else
{
    while( <STDIN> )
    {
        if( $wantUidSearch != 0 )
            {
                if( $_ =~ m/^[^:]*:[^:]*:$wantUidSearch:/ )
                {
                    $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
                    # print "sugma\n";
                    print "$_";
                    $lineCnt++;
                }
            }
            else{
                $_ =~ s/^([[:alnum:]]*):(.*)$/$1/;
                print "$_";
                $lineCnt++;
            }
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