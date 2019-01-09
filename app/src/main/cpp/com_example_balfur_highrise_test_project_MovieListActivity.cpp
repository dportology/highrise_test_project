#include <jni.h>
#include <string>
#include "MovieController.hpp"
#include "MovieController.cpp"
#include <android/log.h>

// Separate file for JNI wrapper functions. These are the functions directly callable by java code
// and will allow the Movie Controller to be used without modification

// Convert jstring to c string.
std::string ConvertJString(JNIEnv* env, jstring str)
{
   const jsize len = env->GetStringUTFLength(str);
   const char* strChars = env->GetStringUTFChars(str, (jboolean *)0);

   std::string Result(strChars, len);

   env->ReleaseStringUTFChars(str, strChars);

   return Result;
}


extern "C"
JNIEXPORT jobjectArray JNICALL Java_com_example_balfur_highrise_1test_1project_MovieListActivity_getMovies
    (JNIEnv *env, jobject obj, jobjectArray oa){

    // Initialize new MovieController object
    MovieController* movieController = new MovieController("path/to/images");

    // Get vector of all movie information from MovieController.cpp
    std::vector<Movie*> movieVector = movieController->getMovies();

    // jclass reference to java Movie object
    jclass cls = env->FindClass("com/example/balfur/highrise_test_project/POJOs/Movie");
    // Java method reference to Movie constructor.
    // Ref for arguments signature [https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html#wp276]
    jmethodID methodId = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;I)V");

    // Java friendly array which will contain all movie objects
    jobjectArray objArray = (env)->NewObjectArray(movieVector.size() ,cls ,0);

    // Create java Movie objects in loop here and add to objArray return object.
    for(int i = 0; i < movieVector.size(); i++) {

        // Convert cstring movie name to jstring
        jstring jstringName = env->NewStringUTF(movieVector[i]->name.c_str());
        // Movie java object created with above cls jclass reference, and method (constructor) signature
        jobject movieObj = env->NewObject(cls, methodId, jstringName, movieVector[i]->lastUpdated);
        (env)->SetObjectArrayElement(objArray, i, movieObj);

    }

    return objArray;

}


extern "C"
JNIEXPORT jobject JNICALL Java_com_example_balfur_highrise_1test_1project_MovieDetailFragment_getMovieDetail
    (JNIEnv *env, jobject obj, jstring name){

    // Initialize new MovieController object
    MovieController* movieController = new MovieController("path/to/images");

    // Use custom method ConvertJString to turn param name from into cString from jstring
    // [https://stackoverflow.com/questions/11558899/passing-a-string-to-c-code-in-android-ndk]
    std::string movieName = ConvertJString(env, name);

    // Call to getMovieDetail in MovieController.cpp using supplied movieName param
    movies::MovieDetail* movieDetail = movieController->getMovieDetail(movieName);

    // Prepare args for the movieDetail Java object. need to be converted from cstring to jstring
    // Not necessary for primitives (see float score below)
    jstring jstringName = env->NewStringUTF(movieDetail->name.c_str());
    jstring jstringDesc = env->NewStringUTF(movieDetail->description.c_str());

    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", movieName.c_str());

    // jclass reference to java MovieDetail object
    jclass movieDetailClass = env->FindClass("com/example/balfur/highrise_test_project/POJOs/MovieDetail");

    // Get vector of all actor information
    std::vector<Actor> actorVector = movieDetail->actors;

    // jclass reference to java Actor object
    jclass actorClass = env->FindClass("com/example/balfur/highrise_test_project/POJOs/Actor");
    // Java method reference to Actor constructor.
    // Ref for arguments signature [https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html#wp276]
    jmethodID actorConstructorId = env->GetMethodID(actorClass, "<init>", "(Ljava/lang/String;ILjava/lang/String;)V");

    // Java friendly array which will contain all actor objects
    jobjectArray actorArray = (env)->NewObjectArray(actorVector.size() ,actorClass ,0);

    // Create java Actor objects in loop here and add to actorArray return object.
    for(int i = 0; i < actorVector.size(); i++) {

        // Convert cstring movie name to jstring
        jstring jstringName = env->NewStringUTF(actorVector[i].name.c_str());
        jstring jstringImageUrl = env->NewStringUTF(actorVector[i].imageUrl.c_str());
        // Movie java object created with above actorClass jclass reference, and method (constructor) signature
        jobject actorObj = env->NewObject(actorClass, actorConstructorId, jstringName, actorVector[i].age, jstringImageUrl);
        (env)->SetObjectArrayElement(actorArray, i, actorObj);

    }

    // Java method reference to MovieDetail constructor.
    // Ref for arguments signature [https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html#wp276]
    jmethodID methodId = env->GetMethodID(movieDetailClass, "<init>", "(FLjava/lang/String;Ljava/lang/String;[Lcom/example/balfur/highrise_test_project/POJOs/Actor;)V");
    jobject returnObj = env->NewObject(movieDetailClass, methodId, movieDetail->score, jstringName, jstringDesc, actorArray);

    return returnObj;
}


extern "C"
JNIEXPORT jstring JNICALL Java_com_example_balfur_highrise_1test_1project_MovieListActivity_getMovieImage
    (JNIEnv *env, jobject obj, jstring name){

    // Use custom method ConvertJString to turn param name from into cString from jstring
    // [https://stackoverflow.com/questions/11558899/passing-a-string-to-c-code-in-android-ndk]
    std::string movieName = ConvertJString(env, name);

    // Initialize new MovieController object
    MovieController* movieController = new MovieController("path/to/images");

    // Get vector of all movie information from MovieController.cpp
    std::vector<unsigned char> movieImageData = movieController->getMovieImage(movieName);

    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "BEFORE");
    for (unsigned i=0; i < movieImageData.size(); i++) {
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", movieImageData[i]);
    }

    return name;

}