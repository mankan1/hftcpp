for i in $(find -maxdepth 1 -type d | grep -v '^\.$' | sed 's/\.\///' ); do
      echo $i;
          ctags -f ~/tmp_tags/$i.tags -R --c++-kinds=+p --fields=+iaS --extra=+q --languages=c++ --sort=foldcase $i;
        done
