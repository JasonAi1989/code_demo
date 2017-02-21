#!/usr/bin/perl -w

use lib ("/home/eaizhao/.local/lib64/perl5");
use lib ("/home/eaizhao/.local/share/perl5");


use strict;
use Net::SSH::Perl;

use Crypt::Digest::SHA256 qw( sha256 );

my $host = '147.128.118.143';
my $user = 'ejbca';
my $password = 'ejbca';

my $ssh = Net::SSH::Perl->new ($host);
$ssh->login ($user, $password);
