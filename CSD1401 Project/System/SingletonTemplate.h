/*!
@file       SingletonTemplate.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains a singleton template with the public functions
			to get and destroy the instance.
*//*_______________________________________________________________________*/
#pragma once

template <typename T>
class SingletonTemplate
{
private:
	//Instance of the singleton
	static T* instance;

protected:
	//Constructor
	SingletonTemplate()
	{

	}

	//Destructor
	~SingletonTemplate()
	{

	}

public:

	/**
	 @brief Get the current instance of the singleton, creates it if it
			doesn't exist
	 @param void
	 @return templated pointer to the instance
	 */
	static T* GetInstance(void)
	{
		//Sets a new instance if it does not exist
		if (instance == nullptr)
			instance = new T();

		return instance;
	}

	/**
	 @brief Destroy the instance if it exists, and resets it to nullptr
	 @param void
	 @return void
	 */
	static void DestroyInstance(bool destroy = false)
	{
		//Checks if there is a current instance of the singleton
		if (destroy && instance)
		{
			//Delete the instance and reset it to nullptr
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T>
T* SingletonTemplate<T>::instance = nullptr;