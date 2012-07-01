#! /usr/bin/perl
#�������perlscript ����Ҫ��װperl����������ɫ�ġ�
#perllib ������������d:\perl\lib
use warnings;

sub countFileLine;
sub get_dir;

$totallines = 0;
$totalfiles = 0;
$totaldirs = 0;

my %filecatagorycount;
my %filecatagorysize;

get_dir @ARGV;
print "�����ļ���������".$totallines . "   " .$totallines/10000;print "����\n";
print "�����ļ�������".$totalfiles;print "\n";
print "�����ļ���������".$totaldirs;print "\n";
# ��ӡÿ�������ļ�����
foreach(sort keys%filecatagorycount) #����
{
	print "��׺��Ϊ�� $_ ���ļ����� => $filecatagorycount{$_}","   �ļ���С => ",$filecatagorysize{$_}/1024/1024 ,"M","\n";
}
my @filter = qw(h cpp java pro pri );
my $filtersize = 0;
foreach (@filter)
{
	print "\t".$_ . "\n";
	$filtersize+=$filecatagorysize{$_}/1024/1024;
	#print; #��ӡĬ�ϱ���
}
print "ͨ��[ @filter ] ���˺��ܴ�СΪ  ".$filtersize,"M\n";
# ��ȡ�ļ�����
sub countFileLine 
{
    my $file = shift;
    my $count = 0;
    open (FH,"$file") or die "Can't open the file:$!\n";
    ++$count while (<FH>);
    close FH;
	my @lines = split(/\./,$file);
	my $linescount = @lines;
	$filesize = -s $file;
	#print $file.$filesize ; print "\n";
	# �鴦�ַ�������
	$len = rindex $lines[$linescount-1]."\$", "\$";
	if($linescount > 1 && $len < 6)
	{
		$filecatagorycount{$lines[$linescount-1]}++;
		$filecatagorysize{$lines[$linescount -1]}+= $filesize;
	}
	else
	{
		$filecatagorycount{"NOEXT"}++;
		$filecatagorysize{"NOEXT"}+= $filesize;
	}
	
	#print @lines;print "\n";
    # print "$count lines in $file\n";
    $totallines += $count;
	$totalfiles++;
}

# ��ȡĿ¼�ļ���
sub get_dir 
{
    my $dir = shift;
	print "$dir\n";
    opendir (DIR,"$dir") or die "Can't open dir:$!";
    my @file = readdir(DIR);
    closedir(DIR);
    foreach (@file)
	{
		next if $_ eq '.' or $_ eq '..';
		my $file = "$dir/$_";
		if (-d $file)
		{
			 get_dir($file);
		} 
		else
		{
			countFileLine($file) if -T $file;
		}
	}
	$totaldirs++;
}
