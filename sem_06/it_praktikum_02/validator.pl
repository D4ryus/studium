#!/usr/bin/perl
# author: Tux
# to use run 'cpan XML::LibXML' only once, enviroment variables should be set
# atomaticly (check ~/.bashrc resource is needed)

use strict;
use warnings;

use XML::LibXML;
use Data::Dumper;

my $input = slurpstdin();
my $parser = XML::LibXML->new();
$parser->validation(1);

my $validated = $parser->parse_string($input);


sub slurpstdin {
        my $input = "";
        while (<>) {
                $input = $input.$_;
        }
        return $input;
}
