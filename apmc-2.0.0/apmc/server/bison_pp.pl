#!/usr/bin/perl

my $input = $ARGV[0];
my $linenb = 1;

sub replace_for_status
{
    my ($sreq, $source) = @_;
    my $status = 0;
    open(REPLACE, "<$source") or die " could not open $source in $input:$linenb : $!\n";
	while(<REPLACE>)
	{
	    if( $_ =~ /^%%$/ )
	    {
		$status++;
		last if($status > $sreq);
	    } else {
		print $_ if($status == $sreq);
	    }
	}
    close(REPLACE);
}

open(INPUT, "<$input") or die "could not open $input : $!\n";

my $source;
my $line;
while(<INPUT>)
{
    $line = $_;
    if( ($source) = ($line =~ /^\#include_precedence.*<(.*)>$/ ) )
    {
	replace_for_status(0, $source);
    } elsif( ($source) = ($line =~ /^\#include_rules.*<(.*)>$/ ) )
    {
	replace_for_status(1, $source);
    } elsif ( ($source) = ($line =~ /^\#include_additional_code.*<(.*)>$/) )
    {
	replace_for_status(2, $source);
    } else {
	print $line;
    }
    $linenb++;
}

close(INPUT);
