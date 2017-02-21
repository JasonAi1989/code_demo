#!/usr/bin/perl -w

use lib ("/home/eaizhao/.local/lib64/perl5");
use lib ("/home/eaizhao/.local/share/perl5");
use strict;
use Net::OpenSSH;
 
my $host = '147.128.118.143';

                   
my $ssh = Net::OpenSSH->new('ejbca:ejbca@147.128.118.143');
my ($stdout,$stderr) = $ssh->capture2("df -h");
if($stdout){
                       print $stdout;
                       } else {
                           print $ssh->error;
                               $stderr and print $stderr;
                               }
