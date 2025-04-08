#include <public/ccdisplaysmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCDisplaysMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCDisplaysMng &act,
	 TEDROOMUInt8 * EDROOMpVarVDisplays7SegValue ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	DisplaysMngCtrl(EDROOMcomponent.DisplaysMngCtrl),
	Timer(EDROOMcomponent.Timer),
	VDisplays7SegValue(EDROOMpVarVDisplays7SegValue)
{
}

CCDisplaysMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	DisplaysMngCtrl(context.DisplaysMngCtrl),
	Timer(context.Timer),
	VDisplays7SegValue(context.VDisplays7SegValue)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCDisplaysMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCDisplaysMng::EDROOM_CTX_Top_0::FIncreaseDisplays()

{

nexys_srg_gpio_increase_seg_7seg_array(VDisplays7SegValue);

}



void	CCDisplaysMng::EDROOM_CTX_Top_0::FProgDisplaysRefresh()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
  interval = Pr_Time(0,1000);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCDisplaysMng::EDROOM_CTX_Top_0::FRefreshDisplays()

{

for(uint16_t i=0; i < 1000 ; i++ )
	nexys_srg_gpio_seg_7seg_array(8,VDisplays7SegValue);

}



void	CCDisplaysMng::EDROOM_CTX_Top_0::FSendDisplaysReady()

{

for(uint8_t i=0; i < 8 ; i++)
	VDisplays7SegValue[i]=0;
 
nexys_srg_gpio_set_7seg_digit(7, 0) ;
   //Send message 
   DisplaysMngCtrl.send(SDisplaysReady); 
}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCDisplaysMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCDisplaysMng&act):
		EDROOM_CTX_Top_0(act,
			VDisplays7SegValue)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCDisplaysMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Start
			case (Start):
				//Execute Action 
				FProgDisplaysRefresh();
				//Send Asynchronous Message 
				FSendDisplaysReady();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is RefreshDisplays
			case (RefreshDisplays):
				//Execute Action 
				FProgDisplaysRefresh();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is IncreaseDisplays
			case (IncreaseDisplays):
				//Execute Action 
				FIncreaseDisplays();
				//Next State is Ready
				edroomNextState = Ready;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state Idle
			case (Idle):
				//Arrival to state Idle
				edroomCurrentTrans=EDROOMIdleArrival();
				break;

				//Go to the state Ready
			case (Ready):
				//Execute Entry Action 
				FRefreshDisplays();
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCDisplaysMng::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCDisplaysMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CCDisplaysMng::EDROOM_SUB_Top_0::EDROOMIdleArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SDisplaysStart): 

				 if (*Msg->GetPInterface() == DisplaysMngCtrl)
				{

					//Next transition is  Start
					edroomCurrentTrans.localId= Start;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCDisplaysMng::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  RefreshDisplays
					edroomCurrentTrans.localId= RefreshDisplays;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (SIncreaseDisplays): 

				 if (*Msg->GetPInterface() == DisplaysMngCtrl)
				{

					//Next transition is  IncreaseDisplays
					edroomCurrentTrans.localId= IncreaseDisplays;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



