<?php

class User {
    private $_db;
    private $_data;
    private $_tbName;
    private $_userId;
    private $_sessionName;
    private $_isLoggedIn;

    /**
     * User Constructor
     * @param type $user
     */
    public function __construct($user = null){
        $this->_db = Database::getInstance();
        $this->_sessionName = Config::get('session/user_session');
        $this->_tbName = Config::get('table_name/users');
        $this->_userId = Config::get('table_col/users/user_id');
        if(!$user){
            if(Session::exists($this->_sessionName)){
                $user = Session::get($this->_sessionName);
                if($this->find($user)){
                    $this->_isLoggedIn = true;
                }
            }
        } else {
            $this->find($user);
        }
    }

    /**
     * save a user
     * @param type $data
     * @param type $id
     * @return boolean
     * @throws Exception
     */
    public function save($data = array(), $id = null){
        if (isset($id) && !empty($id)) {
            // update user
            if ($this->_db->update($this->_tbName, $data, array($this->_userId , '=', Input::sanitize($id)))) {
                return true;
            }else{
                throw new Exception('Exception thrown: There was a problem updating your account');
            }
        } else{
            // create user
            if($this->_db->insert($this->_tbName, $data)){
                return $this->_db->pdo()->lastInsertId();
            } else {
                throw new Exception('Exception thrown: There was a problem creating your account');
            }
        }
    }

    /**
     * login a user
     * @param type $username
     * @param type $password
     * @return boolean
     */
    public function login($username = null, $password = null){
        if($this->find($username)){
            if($this->getData()->password === Hash::generate_hash($password, $this->getData()->salt)){
                Session::set($this->_sessionName, $this->getData()->id);
                return true;
            }
        }
        return false;
    }

    /**
     * logout a user
     * @return type
     */
    public function logout(){
        if($this->isLoggedIn())
            Session::delete($this->_sessionName);
        return;
    }

    /**
     * find a user and return the user data
     * @param null $user
     * @return bool
     */
    private function find($user = null){
        if($user){
            $field = (is_numeric($user)) ? 'id' : 'username';
            $user_data = $this->_db->select('users', [$field, '=', $user]);
            if($this->_db->getCount()){
                $this->_data = $user_data->getRow();
                return true;
            }
        }
        return false;
    }
    
    /**
     * read all users or a single user
     * @param type $id
     * @throws Exception
     */
    public function read($id = null){
        if (isset($id) && !empty($id)) {
            if (($single_user = $this->_db->select($this->_tbName, array($this->_userId, '=', Input::sanitize($id)))->getRow()) != NULL) {
                $this->_data = $single_user;
            } else {
                throw new Exception("Exception thrown: No user with the ID {$id} is found");
            }
        } else {
            if($all_users = $this->_db->select($this->_tbName)->getResult()){
                $this->_data = $all_users;
            } else {
                throw new Exception("Exception thrown: No users were found");
            }
        }
    }

    /**
     * delete a user
     * @param type $id
     * @return boolean
     * @throws Exception
     */
    public function delete($id) {
        if($this->_db->delete($this->_tbName, array($this->_userId, '=', Input::sanitize($id)))){
            if($this->_db->getCount() == 0){
                throw new Exception("Exception thrown: User with ID = {$id} not found. No User deleted.");
            } else {
                return true;
            }
        }
        return false;
    }
    
    /**
     * return user data
     * @return mixed
     */
    public function getData(){
        return $this->_data;
    }

    /**
     * return user log in state
     * @return bool
     */
    public function isLoggedIn(){
        return $this->_isLoggedIn;
    }
    
    /**
     * set user id
     * @param type $string
     */
    public function setUserId($string = null){
        if(isset($string) && !empty($string)){
            if(!is_numeric($string)){
                $this->_userId = $string;
            }
        } else {
            $this->_userId = 'id';
        }
    }
    
    /**
     * get user id
     * @return type
     */
    public function getUserId(){
        return $this->_userId;
    }
}