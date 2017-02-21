#!/usr/bin/perl -w

print("test\n");

@output = (25, 30, 40, 'asdf', 'asdfasdf', "123", "345", "aaaa", "lll", "999"); 
    for( $a = 0; $a < 10; $a = $a + 1 ){ 
        print("TC1 Error: $a -- $output[$a]\n");    
    }

    $ret=grep(/as(.)*/, @output);
    print("$ret\n");
    @a=grep(/as*/, @output);
    print("@a\n");
