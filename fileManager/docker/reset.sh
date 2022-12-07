kubectl delete deployment kub-fm
#kubectl delete service filemanager-entrypoint
docker image rm mcabreralinan/filemanager:1.3
docker build .
