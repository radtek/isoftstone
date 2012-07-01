

#ifndef __DATETIME_ICE
#define __DATETIME_ICE
// Slice 
module DataTypes 
{ 
  struct Date 
  { 
   int nYear; 
   byte nMonth; 
   byte nDay; 
   byte nHour; 
  }; 
 
  struct Time 
  { 
   byte nHour; 
   byte nMinute; 
   byte nSecond; 
   int nMilisecond; 
   int nUtcOffset; 
  }; 
 
  struct DateTime 
  { 
   int nYear; 
   byte nMonth; 
   byte nDay; 
   byte nHour; 
   byte nMinute; 
   byte nSecond; 
   int nMilisecond; 
   int nUtcOffset; 
  }; 
};


#endif