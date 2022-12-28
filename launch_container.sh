docker run -it --rm --name=gbx_test_container --mount type=bind,source=${PWD},target=/home/gbx_test gbx_test_image  bash /home/gbx_test/build_and_run.sh
