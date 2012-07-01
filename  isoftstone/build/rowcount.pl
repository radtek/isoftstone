#! /usr/bin/perl
#如果运行perlscript 必须要安装perl，不能用绿色的。
#perllib 环境变量加上d:\perl\lib
use warnings;

sub countFileLine;
sub get_dir;

$totallines = 0;
$totalfiles = 0;
$totaldirs = 0;

my %filecatagorycount;
my %filecatagorysize;

get_dir @ARGV;
print "所有文件总行数：".$totallines . "   " .$totallines/10000;print "万行\n";
print "所有文件总数：".$totalfiles;print "\n";
print "所有文件夹总数：".$totaldirs;print "\n";
# 打印每种类型文件个数
foreach(sort keys%filecatagorycount) #排序
{
	print "后缀名为【 $_ 】文件个数 => $filecatagorycount{$_}","   文件大小 => ",$filecatagorysize{$_}/1024/1024 ,"M","\n";
}
my @filter = qw(h cpp java pro pri );
my $filtersize = 0;
foreach (@filter)
{
	print "\t".$_ . "\n";
	$filtersize+=$filecatagorysize{$_}/1024/1024;
	#print; #打印默认变量
}
print "通过[ @filter ] 过滤后总大小为  ".$filtersize,"M\n";
# 读取文件行数
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
	# 查处字符串长度
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

# 读取目录文件行
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
