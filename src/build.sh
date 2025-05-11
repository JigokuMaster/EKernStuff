set -e

WD=$(pwd)
winscw_build()
{
	cd HelloLDD/group
	echo "#define __WINSCW__" > buildconf.h
	./abld reallyclean winscw udeb
	bldmake bldfiles
	./abld build -v winscw udeb
	cd $WD
	./abld reallyclean winscw udeb
	bldmake bldfiles
	./abld build -v winscw udeb

}

gcce_build()
{
	cd HelloLDD/group
	echo "#define __GCCE__" > buildconf.h
	./abld reallyclean gcce udeb
	bldmake bldfiles gcce
	./abld build -v gcce urel
	cd $WD
	./abld reallyclean gcce urel
	bldmake bldfiles
	./abld build -v gcce urel
}

#winscw_build
gcce_build