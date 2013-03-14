env = Environment()

sources = Split("""
	src/Atom.cpp
	src/AtomIndex.cpp
	src/Drawing.cpp
	src/GLWindow.cpp
	src/Link.cpp
	src/main.cpp
	src/Model.cpp
	src/PhyGLMode.cpp
	src/PhyLoader.cpp
	src/PhyWriter.cpp
	src/Workers.cpp
	src/YamlGLMode.cpp
	src/YamlLoader.cpp
	src/YamlPhyMode.cpp
	src/burden/Burden.cpp
""")

libraries = Split("""
	GL
	GLU
	glut
	boost_thread
	boost_signals
	boost_program_options
	pthread
	yaml-cpp
""")

env.Append(CCFLAGS = ['-pedantic', '-Wall', '-Wextra', '-std=c++11', '-O3'])
env.Append(LIBS = libraries)
env.SetOption('num_jobs', 8)

env.Program(target = 'test', source = sources)
