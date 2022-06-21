#!/usr/bin/perl

=encoding UTF-8

=head1 Sample documentation

=head2 random things:

=over 1

=item yes a very important point

=item absolutely revolutionary

=over 2

=item yet another one, but this one is B<DEEPER>

=back

=item and this one is not, but it is I<TILTED>, also have a bar: E<verbar>

=item last important note L<I CAN DO A LINK!|https://www.youtube.com/watch?v=dQw4w9WgXcQ>

=back

=head2 random copypasta

Today at school my friend said she didn't like Dream.
I was so angry. I got up in front of the class and said “You may not like B<Dream>, but he saved my life. i was at my lowest point,
but his channel saved me. sorry if that's not good enough for you.”
and then everyone started to clap slowly and my teacher made her go to guidance.
My teacher held me after class and said “I love Dream too.”
Needless to say, I got an A+ in the class.

B<My wife poops in the shower and stomps it down the drain. Not a joke. >
She recently told me this and I've been living with it for weeks now. She even broke the news to me while laughing about it. 
"You know what a waffle stomp is?", she asked me as she laughed and laughed so hard she started crying! 
I feel disgusted and betrayed. I can't even look at her over breakfast anymore before I head off to work and while at work all I can do is wonder to myself, 'is she doing it right now?'. 
Apparently this has been going on for years! Says she uses all the scented candles she obsessively buys online to mask the smell. 
I work 12- 15 hour days so plenty of time to cover her shit stink. A few times we've had to snake the drain due to a clog. 
Now I know why. 
I'm not sure I can live this life anymore.

=cut

use v5.10;
use warnings;
use strict;

my $greeting="if you see this something is wrong";
my $user=$ENV{USER};

if( defined $ARGV[0] ){
    $greeting=$ARGV[0];
}
else{
    $greeting="this is the default greeting, welcome ";
}

$greeting="$greeting$user";
print("$greeting\n");
