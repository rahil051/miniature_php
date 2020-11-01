<?php
session_start();

define('D', DIRECTORY_SEPARATOR);
$root_dir = __DIR__;
$root_dir_ex = explode('\\', $root_dir);
$discard = array_pop($root_dir_ex);
$root_dir = implode('\\', $root_dir_ex);
define('ROOT', $root_dir);

/**
* Credentials for the website
* mysql         => database configuration               [db_driver > db_credentials]
* remember      => cookie configuration                 [cookie > cookie_credentials]
* session       => user state management configuration  [session > session__credentials]
* redirect      => redirect to paths                    [redirect > redirect_path]
* table_name    => database table names                 [table_name > names]
* table_col     => table columns                        [table_columns > cols]
*/

/***** DO NOT MODIFY THE KEYS! *****/
$GLOBALS['config'] = array(
    'mysql' => array(
        'host' => '127.0.0.1',
        'username' => 'root',
        'password' => '',
        'db_name' => 'careem'
        ),
    'remember' => array(
        'cookie_name' => 'hash',
        'cookie_expiry' => 604800
        ),
    'session' => array(
        'user_session' => 'user',
        'token_name' => 'token'
        ),
    'redirect' => array(
        '404' => 'includes/404.php'
        ),
    'table_name' => array(
        'users' => 'users',
        'user_session' => 'user_session'
        ),
    'table_col' => array(
        'users' => array(
            'user_id' => 'id'
            ),
        'user_session' => array(
            'hash' => 'hash',
            'user_id' => 'uid'
            )
        )
    );

/***** DO NOT MODIFY THE FOLLOWING LINES OF CODE! *****/
spl_autoload_register(function($class){
    require_once 'classes/'.$class.'.inc';
});

if(Cookie::exists(Config::get('remember/cookie_name')) && !Session::exists(Config::get('session/session_name'))){
    $hash = Cookie::get(Config::get('remember/cookie_name'));
    $hash_check = Database::getInstance()->select(Config::get('table_name/user_session'), array( Config::get('table_col/user_session/hash'), '=', $hash));
    if($hash_check->getCount()){
        $uid = Config::get('table_col/users/user_id');
        $user = new User($hash_check->getRow()->$uid);
        $user->login();
    }
}