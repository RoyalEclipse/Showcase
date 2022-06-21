#!/usr/bin/perl

use v5.10;
use warnings;
use strict;

if( $#ARGV != 1 || !$ARGV[0] || !$ARGV[1] )
{
    print STDERR "wrong amount of arguments, ending with 2\n";
    exit 2;
}

my $foundCount = 0;
my $arrowLine = "";
my $offset = 0;
my $result = 0;
my @indexes;

my @letters = split(//, $ARGV[1]);
foreach ( @letters )
{
    if( $_ =~ m/[\{\}\[\]\(\)\^\$\.\|\*\+\?\\]/ )
    {
        print STDERR "illegal character encountered 3\n";
        exit 3;
    }
}

my @letterstwo = split(//, $ARGV[0]);
foreach ( @letterstwo )
{
    if( $_ =~ m/[\{\}\[\]\(\)\^\$\.\|\*\+\?\\]/ )
    {
        print STDERR "illegal character encountered 3\n";
        exit 3;
    }
}

# print "$ARGV[0]\n";
# print "$ARGV[1]\n";

while( $result != -1 )
{
    $result = index( $ARGV[0], $ARGV[1], $offset );    
    # print "result is: $result\n";
    if ( $offset  == 0 && $result == 0 ){ $offset = 1; }
    $offset = $offset + $result;
    if( $result != -1 ){ $foundCount++; push( @indexes, $result ); } 
    # print "looping here\n";
}

if ( $foundCount == 0 ) {
    print STDERR "1\n";
    print "$ARGV[1] not found.\n";
    exit 1;
}
else{
    my $loopcounter = 0;
    my $arrowLineIndex = 0;
    
    while( ! ( $loopcounter > $#indexes + 1 ) && $arrowLineIndex < length($ARGV[0]) && $loopcounter < $#indexes + 1 )
    {
        # print "is $arrowLineIndex equal to $indexes[$loopcounter]";
        if( $arrowLineIndex == $indexes[$loopcounter] )
        {
            # print"this";
            $arrowLine = $arrowLine."^";
            $arrowLineIndex++;
            $loopcounter++;
        }
        else
        {
            # print"that";

            $arrowLine = $arrowLine." ";
            $arrowLineIndex++;
        }
        # print "looping there\n";
        # print "$loopcounter vs $#indexes + 1\n"
    }
    
    print "$ARGV[0]\n";
    print "$arrowLine\n";

    exit 0;
}