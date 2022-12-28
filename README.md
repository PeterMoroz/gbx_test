To run the service:

1. Create the image with create_image.sh (It will create docker image with name 'gbx_test_image').
2. Launch docker container with launch_container.sh. The script launches container from image 'gbx_test_image', and execute script build_and_run.sh in running container. 
Script build_and_run.sh will build the project, run unit tests and launch the service.

3. You can check REST API provided by service with CURL. The service is listening incoming requests on port 8000.

For example (172.17.0.2 is IP address of container):
- add user (the user's ID will be returned in case of success)
 peter@peter-X751MA:~$ curl -X POST http://172.17.0.2:8000/api/users/ --data 'username=peter&password=12345678'
 
- get user's info (the user's info will be returned in case of success)
 peter@peter-X751MA:~$ curl -X GET http://172.17.0.2:8000/api/users/<userId>
 
- change user's password
 peter@peter-X751MA:~$ curl -X PUT http://172.17.0.2:8000/api/users/ --data 'username=peter&password=1234567890'

- get user's info again
 peter@peter-X751MA:~$ curl -X GET http://172.17.0.2:8000/api/users/<userId>
 
- delete user
 peter@peter-X751MA:~$ curl -X DELETE http://172.17.0.2:8000/api/users/<userId>
