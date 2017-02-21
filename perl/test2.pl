#!/usr/bin/perl -w

my @output=("num of trusted-certificate: 1", "name: TC-20170216-165931-chain_ca.cert.pem", "name: TC-20170216-165731-chain_ca.cert.pem");
my @certs;

foreach(@output)
{
    my @sp=split(/:/, $_);
#    print("sp->@sp\n");
    my @cert=grep(/TC-(.)*/, @sp);
    $size=@cert;
    if($size == 1)
    {
        print("cert->@cert\n");
        push(@certs, $cert[0]);
    }
}

        print("certs->@certs\n");
