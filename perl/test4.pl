
package Person;
use strict;

sub new
{
    my $class = shift;
    my $self = {
        _ip => shift,
        _firstName => shift,
        _lastName  => shift,
        _ssn       => 10,
        1          => 0,
        2          => 0,
        3 => "",
    };
    # 输出用户信息
    print "名字：$self->{_firstName}\n";
    print "姓氏：$self->{_lastName}\n";
    print "编号：$self->{_ssn}\n";
    bless $self, $class;
    return $self;
}
sub test
{
    my ($self, $a, $b) = @_;

    $self->{1} = $a;
    print "1:$self->{1}\n";
    my $ip = $self->{_ip};
    print "IP:$ip\n";
}
sub test2{
    my $self = shift;
    my $ip = $self->{_ip};
    print "IP:$ip\n";
    my $tt="eiahaoa";
    my $port=3;
    my $tt2="";
    if($tt == $self->{$port})
    {
        print "why? $tt, $self->{$port}\n";
    }
    if($tt == $tt2)
    {
        print "really?\n"
    }
}

package main;
my $object = new Person( "12.12.12.11", "小明", "王", 23234345);
$object->test(10, 20);
$object->test2();
my $tt="eiahaoa";
my $tt2="";
if($tt2 && $tt==$tt2)
{
    print "really2?\n"
}
if($tt==$tt2)
{
    print "really3?\n"
}
