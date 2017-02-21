#!/usr/bin/perl -w
use strict;
use Net::Telnet;

my $password = 'Spitfire_12345';
my $username = 'cde';
my $prompt   = '/\[.*?\](router6000|bash|sf-rp-p1s|DUT).*?[#|$|>]|ok $|bash.*/';
my $host     = '10.170.117.250';
my $cmd1     = 'show context all';
my $cmd2     = '/bin/ls -l';

my $conn = new Net::Telnet(
   Timeout=>60,
   Prompt=>$prompt,
   );
$conn->open($host);
$conn->login($username,$password);

my @output = $conn->cmd($cmd1);
print "Output:@output";
@output = $conn->cmd($cmd2);
print "Output:@output";

$conn->close;
