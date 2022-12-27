from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add gpstime src files.
if GetDepend('PKG_USING_GPSTIME'):
    src += Glob('src/GPSTime.c')

if GetDepend('PKG_USING_GPSTIME_SAMPLE'):
    src += Glob('examples/time-test.c')

# add gpstime include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('gpstime', src, depend = ['PKG_USING_GPSTIME'], CPPPATH = path)

Return('group')
