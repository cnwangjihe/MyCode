def get_size(start_path = '.'):
    total_size = 0
    for dirpath, dirnames, filenames in os.walk(start_path):
        for f in filenames:
            fp = os.path.join(dirpath, f)
            total_size += os.path.getsize(fp)
    return total_size

def Get_Csv(FileName,Dir):
	with open(FileName, 'wb') as f:
		f.write(bytes([0xEF, 0xBB, 0xBF]))
		b = list(filter(os.path.isdir, map(lambda x: os.path.join(Dir, x), os.listdir(Dir))))
		for item in b:
#			print(item)
#			item = os.path.join(Dir, item)
			r = re.match( r"^\[(.*?)\] ?(\[?[^\[\n]*)(\[.*\])?$", os.path.split(item)[1])
			if r is not None:
				print(item)
				f.write('{},{},{}\n'.format(r.group(1), r.group(2), get_size(item)).encode())
