#!/usr/bin/perl

use v5.10;
use warnings;
use strict;

$|=1;

BEGIN{
    unless( defined $ARGV[0] ){
        print "gimme a number man\n";
        exit 0;
    }

}

my $timer = $ARGV[0];
my $oamount = $timer;

if($timer > 2){
    $oamount = $timer;
}
else{
    $oamount = 2;
}

my $boom = "B";
while($oamount > 0){
    $boom = $boom."O";
    $oamount--;
}
$boom = $boom."M!";

while( $timer > 0 ){
    print $timer." ";
    sleep 1;
    $timer--;
}

print "$boom\n"