package com.opensdk.utils;

import java.lang.reflect.Method;
import java.util.List;

import android.content.Context;

public class SpecialInitInfo {

	private String initClass=null;
	private String staticMethod=null;
	private List<String> instanceMethods=null;
	
	
	public void invoke(Context content){
		
		if(initClass!=null && staticMethod!=null){
			try {
				Class<?> cls=Class.forName(initClass);

				if(instanceMethods!=null && !instanceMethods.isEmpty()){
					//have instance method
					Method m=cls.getMethod(staticMethod, new Class[]{});
					Object obj=m.invoke(cls, new Object[]{});
					
					int i=0;
					int size=instanceMethods.size();
					
					cls=obj.getClass();
					for(String iter:instanceMethods){
						if(++i==size){
							//last object
							m=cls.getMethod(iter, new Class[]{Context.class});
							m.invoke(cls, new Object[]{content});
						}else{
							m=cls.getMethod(iter, new Class[]{});
							obj=m.invoke(obj, new Object[]{});
						}
					}
				}else{
					//only static method
					Method m=cls.getMethod(staticMethod, new Class[]{Context.class});
					m.invoke(cls, new Object[]{content});
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	public boolean haveInstanceMethod(){
		return instanceMethods!=null && !instanceMethods.isEmpty();
	}
	
	public String getInitClass() {
		return initClass;
	}
	
	public void setInitClass(String initClass) {
		this.initClass = initClass;
	}
	
	public String getStaticMethod() {
		return staticMethod;
	}
	
	public void setStaticMethod(String staticMethod) {
		this.staticMethod = staticMethod;
	}
	
	public List<String> getInstanceMethods() {
		return instanceMethods;
	}
	public void setInstanceMethods(List<String> instanceMethods) {
		this.instanceMethods = instanceMethods;
	}
	
	

}
