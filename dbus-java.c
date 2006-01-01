#include "org_freedesktop_dbus_DBusConnection.h"
#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

DBusConnection* conn;

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_connect
 * Signature: (I)I
 */
JNIEXPORT void JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1connect
  (JNIEnv * env, jobject o, jint bus)
{
   const char* address;
   const char* message = NULL;
   DBusError err;
   // initialise the errors
   dbus_error_init(&err);
   jclass dbeclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusException");

   // connect to the bus
   if (org_freedesktop_dbus_DBusConnection_SESSION == bus)
      address = getenv("DBUS_SESSION_BUS_ADDRESS");
   else if (org_freedesktop_dbus_DBusConnection_SYSTEM == bus)
      address = getenv("DBUS_SYSTEM_BUS_ADDRESS");
   else {
      (*env)->ThrowNew(env, dbeclass, "Invalid Bus Type");
      return;
   }

   if (NULL == address) {
      (*env)->ThrowNew(env, dbeclass, "Failed to get Bus Address");
      return;
   }

   conn = dbus_connection_open_private(address, &err);
   
   if (dbus_error_is_set(&err)) {
      message = err.message;
      dbus_error_free(&err); 
   } 
   if (NULL == conn) {
      if (NULL == message)
         (*env)->ThrowNew(env, dbeclass, "Failed to Connect to Bus");
      else
         (*env)->ThrowNew(env, dbeclass, message);
      return;
   }

   return;
}

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_disconnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1disconnect
  (JNIEnv * env, jobject o)
{
   dbus_connection_close(conn);
}

jobjectArray read_params(JNIEnv* env, DBusMessageIter* args, jsize len, jobject connobj)
{
   DBusMessageIter sub;
   jobject vval, jval = NULL;
   jobjectArray members;
   jmethodID mid;
   jstring sig, cname;

   char cbyteval;
   bool cboolval;
   double cdoubleval;
   uint32_t cuintval;
   uint16_t cushortval;
   uint64_t culongval;
   int32_t cintval;
   int16_t cshortval;
   int64_t clongval;
   const char* cstringval;
   char* cclassname;
   jsize i, j, clen;

   jclass fooclass;
   
   fooclass = (*env)->FindClass(env, "java/lang/Object");
   jobjectArray params = (*env)->NewObjectArray(env, len, fooclass, NULL);
   (*env)->DeleteLocalRef(env, fooclass);

   i = 0;
   do {
      if ((*env)->ExceptionOccurred(env)) return params;
      switch (dbus_message_iter_get_arg_type(args)) {
         case DBUS_TYPE_BYTE:
            dbus_message_iter_get_basic(args, &cbyteval);
            fooclass = (*env)->FindClass(env, "java/lang/Byte");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(B)V");
            jval = (*env)->NewObject(env, fooclass, mid, cbyteval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_BOOLEAN:
            dbus_message_iter_get_basic(args, &cboolval);
            fooclass = (*env)->FindClass(env, "java/lang/Boolean");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(Z)V");
            jval = (*env)->NewObject(env, fooclass, mid, cboolval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_INT16:
            dbus_message_iter_get_basic(args, &cshortval);
            fooclass = (*env)->FindClass(env, "java/lang/Short");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(S)V");
            jval = (*env)->NewObject(env, fooclass, mid, cshortval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_UINT16:
            dbus_message_iter_get_basic(args, &cushortval);
            fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/UInt16");
            cintval = cushortval;
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(I)V");
            jval = (*env)->NewObject(env, fooclass, mid, cintval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_INT32:
            dbus_message_iter_get_basic(args, &cintval);
            fooclass = (*env)->FindClass(env, "java/lang/Integer");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(I)V");
            jval = (*env)->NewObject(env, fooclass, mid, cintval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_UINT32:
            dbus_message_iter_get_basic(args, &cuintval);
            fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/UInt32");
            clongval = cuintval;
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(J)V");
            jval = (*env)->NewObject(env, fooclass, mid, clongval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_INT64:
            dbus_message_iter_get_basic(args, &clongval);
            fooclass = (*env)->FindClass(env, "java/lang/Long");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(J)V");
            jval = (*env)->NewObject(env, fooclass, mid, clongval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_UINT64:
            dbus_message_iter_get_basic(args, &clongval);
            fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/UInt64");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(J)V");
            jval = (*env)->NewObject(env, fooclass, mid, clongval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_DOUBLE:
            dbus_message_iter_get_basic(args, &cdoubleval);
            fooclass = (*env)->FindClass(env, "java/lang/Double");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(D)V");
            jval = (*env)->NewObject(env, fooclass, mid, cdoubleval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_STRING:
            dbus_message_iter_get_basic(args, &cstringval);
            jval = (*env)->NewStringUTF(env, cstringval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            break;
         case DBUS_TYPE_OBJECT_PATH:
            dbus_message_iter_get_basic(args, &cstringval);
            vval = (*env)->NewStringUTF(env, cstringval);
            fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusConnection");
            mid = (*env)->GetMethodID(env, fooclass, "getExportedObject", "(Ljava/lang/String;)Lorg/freedesktop/dbus/DBusInterface;");
            jval = (*env)->CallObjectMethod(env, connobj, mid, vval);
            if (NULL == jval) break;
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, vval);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_STRUCT:
            dbus_message_iter_recurse(args, &sub);
            for (j = 1; dbus_message_iter_has_next(&sub); j++) 
               dbus_message_iter_next(&sub);
            dbus_message_iter_recurse(args, &sub);
            jval = read_params(env, &sub, j, connobj);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            break;
         case DBUS_TYPE_VARIANT:
            dbus_message_iter_recurse(args, &sub);
            members = read_params(env, &sub, 1, connobj);
            vval = (*env)->GetObjectArrayElement(env, members, 0);
            fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/Variant");
            mid = (*env)->GetMethodID(env, fooclass, "<init>", "(Ljava/lang/Object;)V");
            jval = (*env)->NewObject(env, fooclass, mid, vval);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, vval);
            (*env)->DeleteLocalRef(env, jval);
            (*env)->DeleteLocalRef(env, members);
            (*env)->DeleteLocalRef(env, fooclass);
            break;
         case DBUS_TYPE_ARRAY:
            // recurse over array
            dbus_message_iter_recurse(args, &sub);
            for (j = 1; dbus_message_iter_has_next(&sub); j++) 
               dbus_message_iter_next(&sub);
            dbus_message_iter_recurse(args, &sub);
            members = read_params(env, &sub, j, connobj);
            
            // get the type signature
            cstringval = dbus_message_iter_get_signature(&sub); 
            sig = (*env)->NewStringUTF(env, cstringval);

            // its a map
            if (cstringval[0] == '{') {
               fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/MapContainer");
               mid = (*env)->GetMethodID(env, fooclass, "<init>", "([[Ljava/lang/Object;Ljava/lang/String;)V");
               jval = (*env)->NewObject(env, fooclass, mid, members, sig);
               if (NULL == jval) break;
               (*env)->SetObjectArrayElement(env, params, i, jval);
               (*env)->DeleteLocalRef(env, jval);
               (*env)->DeleteLocalRef(env, fooclass);
            }

            // its an array
            else {
               fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusConnection");
               mid = (*env)->GetStaticMethodID(env, fooclass, "getJavaType", "(Ljava/lang/String;Ljava/util/Set;Ljava/util/Map;ZZ)Ljava/lang/String;");
               cname = (*env)->CallStaticObjectMethod(env, fooclass, mid, sig, NULL, NULL, true, true);
               (*env)->DeleteLocalRef(env, fooclass);
               if (NULL == cname) break;

               // find the corresponding java class object
               cstringval = (*env)->GetStringUTFChars(env, cname, 0);
               clen = strlen(cstringval);
               cclassname = malloc(clen+1);
               memset(cclassname, 0, clen+1);
               for (j = 0; j < clen; j++)
                  if ('.' == cstringval[j]) 
                     cclassname[j] = '/';
                  else
                     cclassname[j] = cstringval[j];
               vval = (*env)->FindClass(env, cclassname);
               free(cclassname);

               // convert the array to the new type
               fooclass = (*env)->FindClass(env, "org/freedesktop/dbus/ArrayFrob");
               mid = (*env)->GetStaticMethodID(env, fooclass, "type", "([Ljava/lang/Object;Ljava/lang/Class;)[Ljava/lang/Object;");
               jval = (*env)->CallStaticObjectMethod(env, fooclass, mid, members, vval);
               if (NULL == jval) break;
               (*env)->SetObjectArrayElement(env, params, i, jval);

               // tidy up
               (*env)->DeleteLocalRef(env, jval);
               (*env)->DeleteLocalRef(env, vval);
               (*env)->ReleaseStringUTFChars(env, cname, cstringval);
               (*env)->DeleteLocalRef(env, cname);
               (*env)->DeleteLocalRef(env, fooclass);
            }
            (*env)->DeleteLocalRef(env, members);
            (*env)->DeleteLocalRef(env, sig);
            break;
         case DBUS_TYPE_DICT_ENTRY:
            // recurse over array
            dbus_message_iter_recurse(args, &sub);
            jval = read_params(env, &sub, 2, connobj);
            (*env)->SetObjectArrayElement(env, params, i, jval);
            (*env)->DeleteLocalRef(env, jval);
            break;
         default:
            fprintf(stderr, "Ignoring invalid type signature (%c)\n", 
                  dbus_message_iter_get_arg_type(args));
            break;
      }
      i++;
   } while (i < len && dbus_message_iter_next(args));
   
   return params;
}

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_read_write_pop
 * Signature: (I)Lorg/freedesktop/dbus/DBusMessage;
 */
JNIEXPORT jobject JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1read_1write_1pop
  (JNIEnv * env, jobject connobj, jint timeout)
{
   DBusMessage* msg;
   DBusMessageIter args;
   jobject jmsg = NULL;
   jmethodID mid;
   const char* csource;
   const char* cdestination;
   const char* cservice;
   const char* cobjectpath;
   const char* ctype;
   const char* cname;
   char* cclassname;
   jstring source;
   jstring destination;
   jstring service;
   jstring objectpath;
   jstring type;
   jstring name;
   jobjectArray params = NULL;
   jlong serial;
   jlong replyserial;
   jsize len, typelen;
   int i; 

   jclass sigclass; 
   jclass callclass = (*env)->FindClass(env, "org/freedesktop/dbus/MethodCall");
   jclass errclass = (*env)->FindClass(env, "org/freedesktop/dbus/InternalErrorMessage");
   jclass replyclass = (*env)->FindClass(env, "org/freedesktop/dbus/MethodReply");
   jclass dsigclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusSignal");
   // blocking for timeout ms read of the next available message
   dbus_connection_read_write(conn, timeout);
   msg = dbus_connection_pop_message(conn);

   // just return
   if (NULL == msg) return NULL;

   serial = dbus_message_get_serial(msg);
   replyserial = dbus_message_get_reply_serial(msg);
   cobjectpath = dbus_message_get_path(msg);
   if (NULL == cobjectpath) objectpath = NULL;
   else objectpath = (*env)->NewStringUTF(env, cobjectpath);

   ctype = dbus_message_get_interface(msg);
   if (NULL == ctype) type = NULL;
   else type = (*env)->NewStringUTF(env, ctype);

   cname = dbus_message_get_member(msg);
   if (NULL == cname) name = NULL;
   else name = (*env)->NewStringUTF(env, cname);

   csource = dbus_message_get_sender (msg);
   if (NULL == csource) source = NULL;
   else source = (*env)->NewStringUTF(env, csource);

   cdestination = dbus_message_get_destination(msg);
   if (NULL == cdestination) destination = NULL;
   else destination = (*env)->NewStringUTF(env, cdestination);

   cservice = dbus_message_get_destination(msg);
   if (NULL == cservice) service = NULL;
   else service = (*env)->NewStringUTF(env, cservice);


   if (dbus_message_iter_init(msg, &args)) {
      for (len = 1; dbus_message_iter_has_next(&args); len++) 
         dbus_message_iter_next(&args);
      if (!dbus_message_iter_init(msg, &args)) {
         fprintf(stderr, "Reinitialising arguments failed\n");
         return NULL;
      }
      params = read_params(env, &args, len, connobj);
   } else
      params = NULL;

   switch (dbus_message_get_type(msg)) {
      case DBUS_MESSAGE_TYPE_METHOD_CALL:
         mid = (*env)->GetMethodID(env, callclass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;J)V");
         jmsg = (*env)->NewObject(env, callclass, mid, source, service, objectpath, type, name, params, serial);
         if (NULL != params)
            (*env)->DeleteLocalRef(env, params);
         break;
      case DBUS_MESSAGE_TYPE_METHOD_RETURN:
         mid = (*env)->GetMethodID(env, replyclass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;JJ)V");
         jmsg = (*env)->NewObject(env, replyclass, mid, source, objectpath, type, name, params, serial, replyserial);
         if (NULL != params)
            (*env)->DeleteLocalRef(env, params);
         break;
      case DBUS_MESSAGE_TYPE_ERROR:
         cname = dbus_message_get_error_name(msg);
         if (NULL == cname) name = NULL;
         else name = (*env)->NewStringUTF(env, cname);
         mid = (*env)->GetMethodID(env, errclass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;JJ)V");
         jmsg = (*env)->NewObject(env, errclass, mid, source, destination, name, params, serial, replyserial);
         if (NULL != params)
            (*env)->DeleteLocalRef(env, params);
         break;
      case DBUS_MESSAGE_TYPE_SIGNAL:

         if (NULL != ctype) {
            typelen = strlen(ctype);
            cclassname = malloc(typelen+2+strlen(cname));
            memset(cclassname, 0, typelen+2+strlen(cname));
            for (i = 0; i < typelen; i++)
               if ('.' == ctype[i]) 
                  cclassname[i] = '/';
               else
                  cclassname[i] = ctype[i];
            cclassname[typelen] = '$';
            for (i = 0; i < strlen(cname); i++)
               if ('.' == cname[i]) 
                  cclassname[i+1+typelen] = '/';
               else
                  cclassname[i+1+typelen] = cname[i];
            sigclass = (*env)->FindClass(env, cclassname);
            free(cclassname);
            (*env)->ExceptionClear(env);
         } else 
            sigclass = NULL;
         
         if (NULL == sigclass) {
            sigclass = (*env)->FindClass(env, "org/freedesktop/dbus/InternalSignal");
            mid = (*env)->GetMethodID(env, sigclass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J[Ljava/lang/Object;)V");
            jmsg = (*env)->NewObject(env, sigclass, mid, source, objectpath, name, type, serial, params);
         } else {
            mid = (*env)->GetStaticMethodID(env, dsigclass, "createSignal", "(Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;J[Ljava/lang/Object;)Lorg/freedesktop/dbus/DBusSignal;");
            jmsg = (*env)->CallStaticObjectMethod(env, dsigclass, mid, sigclass, source, objectpath, serial, params);
         }
         (*env)->ExceptionDescribe(env);
         
         if (NULL != params)
            (*env)->DeleteLocalRef(env, params);
         
         (*env)->DeleteLocalRef(env, sigclass);
         break;
      default:
         jmsg = NULL;
   }

   // free the message
   dbus_message_unref(msg);
   return jmsg;
}

int append_args(JNIEnv * env, DBusMessageIter* args, jobjectArray params, jobject connobj)
{
   DBusMessageIter sub, sub2;
   jsize i, j;
   jobject item, vitem;
   jobjectArray members, keys, values;
   jclass clazz;
   jclass clazzclass;
   jmethodID mid, isarray;
   jstring type, sig;
   const char* ctype;
   int slen;

   char cbyteval;
   bool cboolval;
   double cdoubleval;
   int16_t cshortval;
   int32_t cintval;
   int64_t clongval;
   uint16_t cushortval;
   uint32_t cuintval;
   uint64_t culongval;
   const char* cstringval;
   char* str;

   if (NULL == params) return 0;

   jsize len = (*env)->GetArrayLength(env, params);
   jclass objectclass = (*env)->FindClass(env, "java/lang/Object");
   jclass dbcclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusConnection");
   jclass dbiclass = (*env)->FindClass(env, "org/freedesktop/dbus/DBusInterface");
   jclass structclass = (*env)->FindClass(env, "org/freedesktop/dbus/Struct");
   jclass listclass = (*env)->FindClass(env, "java/util/List");
   jclass mapclass = (*env)->FindClass(env, "org/freedesktop/dbus/MapContainer");

   
   for (i = 0; i < len; i++) { 
      item = (*env)->GetObjectArrayElement(env, params, i);
      if (NULL == item) {
         fprintf(stderr, "Item number %d is NULL!!\n", i);
         continue;
      }
      clazz = (*env)->GetObjectClass(env, item);
      clazzclass = (*env)->GetObjectClass(env, clazz);
      mid = (*env)->GetMethodID(env, clazzclass, "getName", "()Ljava/lang/String;");
      isarray = (*env)->GetMethodID(env, clazzclass, "isArray", "()Z");

      type = (jstring) (*env)->CallObjectMethod(env, clazz, mid);
      ctype = (*env)->GetStringUTFChars(env, type, 0);
      slen = strlen(ctype);
      if (0 == strncmp(ctype, "java.lang.Boolean", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "booleanValue", "()Z");
         cboolval = (*env)->CallBooleanMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_BOOLEAN, &cboolval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "org.freedesktop.dbus.UInt16", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "intValue", "()I");
         cushortval = (*env)->CallIntMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_UINT16, &cushortval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "org.freedesktop.dbus.UInt32", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "longValue", "()J");
         cuintval = (*env)->CallLongMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_UINT32, &cuintval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "org.freedesktop.dbus.UInt64", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "longValue", "()J");
         culongval = (*env)->CallLongMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_UINT64, &culongval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.Short", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "shortValue", "()S");
         cshortval = (*env)->CallShortMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_INT16, &cshortval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.Integer", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "intValue", "()I");
         cintval = (*env)->CallIntMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_INT32, &cintval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.Long", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "longValue", "()J");
         clongval = (*env)->CallLongMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_INT64, &clongval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.Byte", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "byteValue", "()B");
         cbyteval = (*env)->CallLongMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_BYTE, &cbyteval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.Double", slen)) {
         mid = (*env)->GetMethodID(env, clazz, "doubleValue", "()D");
         cdoubleval = (*env)->CallDoubleMethod(env, item, mid);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_DOUBLE, &cdoubleval)) 
            return -1;
      }
      else if (0 == strncmp(ctype, "java.lang.String", slen)) {
         cstringval = (*env)->GetStringUTFChars(env,(jstring) item, 0);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &cstringval)) 
            return -1;
         (*env)->ReleaseStringUTFChars(env, item, cstringval);
      }
      else if ((*env)->IsInstanceOf(env, item, mapclass)) {
         
         // get sig
         mid = (*env)->GetMethodID(env, mapclass, "getSig", "()Ljava/lang/String;");
         sig = (*env)->CallObjectMethod(env, item, mid);
         cstringval = (*env)->GetStringUTFChars(env, sig, 0);
         
         // get members
         mid = (*env)->GetMethodID(env, mapclass, "getKeys", "()[Ljava/lang/Object;");
         keys = (*env)->CallObjectMethod(env, item, mid);
         mid = (*env)->GetMethodID(env, mapclass, "getValues", "()[Ljava/lang/Object;");
         values = (*env)->CallObjectMethod(env, item, mid);
         slen = (*env)->GetArrayLength(env, keys);
         
         members = (*env)->NewObjectArray(env, 2, objectclass, NULL);

         dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY, cstringval, &sub);
         // strip off the {}
         str = malloc(strlen(cstringval)-2);
         memset(str, 0, strlen(cstringval)-2);
         for (j = 0; j < (strlen(cstringval)-2); j++)
            str[j] = cstringval[j+1];
            
         // iterate over arrays
         for (j = 0; j < slen; j++) {
            // copy this key/value pair
            (*env)->SetObjectArrayElement(env, members, 0, 
               (*env)->GetObjectArrayElement(env, keys, j));
            (*env)->SetObjectArrayElement(env, members, 1, 
               (*env)->GetObjectArrayElement(env, values, j));
            
            // recurse
            dbus_message_iter_open_container(&sub, DBUS_TYPE_DICT_ENTRY, str, &sub2);
            if (0 > append_args(env, &sub2, members, connobj)) return -1;
            dbus_message_iter_close_container(&sub, &sub2);
         }

         dbus_message_iter_close_container(args, &sub);
         
         free(str);
         (*env)->ReleaseStringUTFChars(env, sig, cstringval);
         (*env)->DeleteLocalRef(env, sig);
         (*env)->DeleteLocalRef(env, keys);
         (*env)->DeleteLocalRef(env, values);
         (*env)->DeleteLocalRef(env, members);
      }
      else if ((*env)->CallBooleanMethod(env, clazz, isarray)) {
         mid = (*env)->GetMethodID(env, clazzclass, "getComponentType", "()Ljava/lang/Class;");
         vitem = (*env)->CallObjectMethod(env, clazz, mid);
         mid = (*env)->GetMethodID(env, clazzclass, "isPrimitive", "()Z");
         if ((*env)->CallBooleanMethod(env, vitem, mid))
            return -1;
         mid = (*env)->GetStaticMethodID(env, dbcclass, "getDBusType", "(Ljava/lang/reflect/Type;)Ljava/lang/String;");
         sig = (*env)->CallStaticObjectMethod(env, dbcclass, mid, vitem);
         if ((*env)->ExceptionOccurred(env)) return -1;
         cstringval = (*env)->GetStringUTFChars(env, sig, 0);
         
         dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY, cstringval, &sub);
         if (0 > append_args(env, &sub, item, connobj)) return -1;
         dbus_message_iter_close_container(args, &sub);
         
         (*env)->DeleteLocalRef(env, vitem);
         (*env)->ReleaseStringUTFChars(env, sig, cstringval);
         (*env)->DeleteLocalRef(env, sig);
      }
      else if ((*env)->IsInstanceOf(env, item, structclass)) {
         mid = (*env)->GetMethodID(env, clazz, "getParameters", "()[Ljava/lang/Object;");
         if (NULL == mid) {
            return -1;
         }
         members = (*env)->CallObjectMethod(env, item, mid);
         mid = (*env)->GetMethodID(env, clazz, "getSig", "()Ljava/lang/String;");
         if (NULL == mid) {
            return -1;
         }
         sig = (*env)->CallObjectMethod(env, item, mid, clazz);
         if (NULL == sig) {
            return -1;
         }
         cstringval = (*env)->GetStringUTFChars(env, sig, 0);
         
         dbus_message_iter_open_container(args, DBUS_TYPE_STRUCT, cstringval, &sub);
         if (0 > append_args(env, &sub, members, connobj)) return -1;
         dbus_message_iter_close_container(args, &sub);
         
         (*env)->DeleteLocalRef(env, members);
         (*env)->ReleaseStringUTFChars(env, sig, cstringval);
         (*env)->DeleteLocalRef(env, sig);
      } 
      else if (0 == strncmp(ctype, "org.freedesktop.dbus.Variant", slen)) {
         // get the value out
         mid = (*env)->GetMethodID(env, clazz, "getValue", "()Ljava/lang/Object;");
         members = (*env)->NewObjectArray(env, 1, objectclass, NULL);
         vitem = (*env)->CallObjectMethod(env, item, mid);
         (*env)->SetObjectArrayElement(env, members, 0, vitem);

         // get its type
         (*env)->DeleteLocalRef(env, clazz);
         clazz = (*env)->GetObjectClass(env, vitem);
         mid = (*env)->GetStaticMethodID(env, dbcclass, "getDBusType", "(Ljava/lang/reflect/Type;)Ljava/lang/String;");
         sig = (*env)->CallStaticObjectMethod(env, dbcclass, mid, clazz);
         if ((*env)->ExceptionOccurred(env)) return -1;
         cstringval = (*env)->GetStringUTFChars(env, sig, 0);

         // add container
         dbus_message_iter_open_container(args, DBUS_TYPE_VARIANT, cstringval, &sub);
         if (0 > append_args(env, &sub, members, connobj)) return -1;
         dbus_message_iter_close_container(args, &sub);

         (*env)->DeleteLocalRef(env, vitem);
         (*env)->DeleteLocalRef(env, sig);
         (*env)->ReleaseStringUTFChars(env, sig, cstringval);
         (*env)->DeleteLocalRef(env, members);
      }
      else if ((*env)->IsInstanceOf(env, item, dbiclass)) {
         mid = (*env)->GetMethodID(env, dbcclass, "getExportedObject", "(Lorg/freedesktop/dbus/DBusInterface;)Ljava/lang/String;");
         vitem = (*env)->CallObjectMethod(env, connobj, mid, item);
         if ((*env)->ExceptionOccurred(env)) return -1;
         cstringval = (*env)->GetStringUTFChars(env, vitem, 0);
         if (!dbus_message_iter_append_basic(args, DBUS_TYPE_OBJECT_PATH, &cstringval)) 
            return -1;
         (*env)->ReleaseStringUTFChars(env, vitem, cstringval);
         (*env)->DeleteLocalRef(env, vitem);
      }
      else {
         fprintf(stderr, "Unknown type %s\n", ctype);
      }
      (*env)->DeleteLocalRef(env, item);
      (*env)->ReleaseStringUTFChars(env, type, ctype);
      (*env)->DeleteLocalRef(env, type);
      (*env)->DeleteLocalRef(env, clazz);
      (*env)->DeleteLocalRef(env, clazzclass);
   }
   (*env)->DeleteLocalRef(env, structclass);
   (*env)->DeleteLocalRef(env, listclass);
   (*env)->DeleteLocalRef(env, mapclass);
   return 0;
}

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_send_signal
 * Signature: (Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)I
 */
   JNIEXPORT jint JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1send_1signal
(JNIEnv * env, jobject connobj, jstring objectpath, jstring type, jstring name, jobjectArray params)
{
   int rv;
   dbus_uint32_t serial = 0; // unique number to associate replies with requests
   DBusMessage* msg;
   DBusMessageIter args;

   const char* cobjectpath = (*env)->GetStringUTFChars(env, objectpath, 0);
   const char* cname = (*env)->GetStringUTFChars(env, name, 0);
   const char* ctype = (*env)->GetStringUTFChars(env, type, 0);

   // create a signal and check for errors 
   msg = dbus_message_new_signal(cobjectpath, // object name of the signal
         ctype, // interface name of the signal
         cname); // name of the signal
   if (NULL == msg) 
      return -1;

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   rv = append_args(env, &args, params, connobj);
   if (0 != rv) {
      dbus_message_unref(msg);
      return rv;
   }
   
   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      dbus_message_unref(msg);
      return -1;
   }
   
   dbus_connection_flush(conn);

   // free the message 
   dbus_message_unref(msg);
   (*env)->ReleaseStringUTFChars(env, type, ctype);
   (*env)->ReleaseStringUTFChars(env, name, cname);
   (*env)->ReleaseStringUTFChars(env, objectpath, cobjectpath);
   return serial;
}

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_send_error_message
 * Signature: ([Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1send_1error_1message
  (JNIEnv *env, jobject connobj, jstring destination, jstring name, jlong replyserial, jobjectArray params)
{
   int rv;
   dbus_uint32_t serial = 0; // unique number to associate replies with requests
   DBusMessage* msg;
   DBusMessageIter args;

   const char* cdestination = NULL;
   if (NULL != destination)
      cdestination = (*env)->GetStringUTFChars(env, destination, 0);
   const char* cname = NULL;
   if (NULL != name)
      cname = (*env)->GetStringUTFChars(env, name, 0);

  
   // create a message and check for errors 
   msg = dbus_message_new(DBUS_MESSAGE_TYPE_ERROR);
   if (NULL == msg) 
      return -1;
   if (0 != replyserial)
      dbus_message_set_reply_serial(msg, replyserial);
   dbus_message_set_error_name(msg, cname);
   dbus_message_set_destination(msg, cdestination);

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   rv = append_args(env, &args, params, connobj);
   if (0 != rv) {
      dbus_message_unref(msg);
      return rv;
   }
   
   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      dbus_message_unref(msg);
      return -1;
   }

   dbus_connection_flush(conn);

   // free the message 
   dbus_message_unref(msg);
   if (NULL != cname) (*env)->ReleaseStringUTFChars(env, name, cname);
   if (NULL != cdestination) (*env)->ReleaseStringUTFChars(env, destination, cdestination);
   return serial;
}


/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_call_method
 * Signature: ([Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1call_1method
  (JNIEnv * env, jobject connobj, jstring service, jstring objectpath, jstring type, jstring name, jobjectArray params)
{
   int rv;
   dbus_uint32_t serial = 0; // unique number to associate replies with requests
   DBusMessage* msg;
   DBusMessageIter args;

   const char* cservice = NULL;
   if (NULL != service)
      cservice = (*env)->GetStringUTFChars(env, service, 0);
   const char* cobjectpath = NULL;
   if (NULL != objectpath)
      cobjectpath = (*env)->GetStringUTFChars(env, objectpath, 0);
   const char* cname = NULL;
   if (NULL != name)
      cname = (*env)->GetStringUTFChars(env, name, 0);
   const char* ctype = NULL;
   if (NULL != type)
      ctype = (*env)->GetStringUTFChars(env, type, 0);
  
   // create a message and check for errors 
   msg = dbus_message_new_method_call(cservice, // service name to call
         cobjectpath, // object name of the method
         ctype, // interface name of the method
         cname); // name of the method
   
   if (NULL != cname) (*env)->ReleaseStringUTFChars(env, name, cname);
   if (NULL != ctype) (*env)->ReleaseStringUTFChars(env, type, ctype);
   if (NULL != cservice) (*env)->ReleaseStringUTFChars(env, service, cservice);
   if (NULL != cobjectpath) (*env)->ReleaseStringUTFChars(env, objectpath, cobjectpath);
   
   if (NULL == msg) 
      return -1;

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   rv = append_args(env, &args, params, connobj);
   if (0 != rv) return rv;
   
   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      dbus_message_unref(msg);
      return -1;
   }

   dbus_connection_flush(conn);

   // free the message 
   dbus_message_unref(msg);
   return serial;
}

/*
 * Class:     org_freedesktop_dbus_DBusConnection
 * Method:    dbus_reply_to_call
 * Signature: ([Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_org_freedesktop_dbus_DBusConnection_dbus_1reply_1to_1call
  (JNIEnv *env, jobject connobj,  jstring destination, jstring type, jstring objectpath, jstring name, jlong replyserial, jobjectArray params)
{
   int rv;
   dbus_uint32_t serial = 0; // unique number to associate replies with requests
   DBusMessage* msg;
   DBusMessageIter args;

   const char* cdestination = NULL;
   if (NULL != destination)
      cdestination = (*env)->GetStringUTFChars(env, destination, 0);
   const char* cname = NULL;
   if (NULL != name)
      cname = (*env)->GetStringUTFChars(env, name, 0);
   const char* ctype = NULL;
   if (NULL != type)
      ctype = (*env)->GetStringUTFChars(env, type, 0);
   const char* cobjectpath = NULL;
   if (NULL != objectpath)
      cobjectpath = (*env)->GetStringUTFChars(env, objectpath, 0);
  
   // create a message and check for errors 
   msg = dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_RETURN);
   if (NULL == msg) 
      return -1;
   dbus_message_set_reply_serial(msg, replyserial);
   dbus_message_set_member(msg, cname);
   dbus_message_set_destination(msg, cdestination);
   dbus_message_set_interface(msg, ctype);
   dbus_message_set_path(msg, cobjectpath);


   if (NULL != cname) (*env)->ReleaseStringUTFChars(env, name, cname);
   if (NULL != ctype) (*env)->ReleaseStringUTFChars(env, type, ctype);
   if (NULL != cobjectpath) (*env)->ReleaseStringUTFChars(env, objectpath, cobjectpath);
   if (NULL != cdestination) (*env)->ReleaseStringUTFChars(env, destination, cdestination);

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   rv = append_args(env, &args, params, connobj);
   if (0 != rv) {
      dbus_message_unref(msg);
      return rv;
   }
   
   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      dbus_message_unref(msg);
      return -1;
   }

   dbus_connection_flush(conn);

   // free the message 
   dbus_message_unref(msg);
   return serial;
}