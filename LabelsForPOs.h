// **************************************************
// Custom code for UD100Form
// Created: 26/04/2017 10:15:31 AM
// **************************************************
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using System.Reflection;
using Ice.BO;
using Ice.UI;
using Ice.Lib;
using Ice.Adapters;
using Ice.Lib.Customization;
using Ice.Lib.ExtendedProps;
using Ice.Lib.Framework;
using Ice.Lib.Searches;
using Ice.UI.FormFunctions;


public class Script
{
	// ** Wizard Insert Location - Do Not Remove 'Begin/End Wizard Added Module Level Variables' Comments! **
	// Begin Wizard Added Module Level Variables **

	Infragistics.Win.UltraWinDock.UltraDockManager dock;

	private EpiDataView edvUD100A;
	private DataView UD100A_DataView;
	// End Wizard Added Module Level Variables **

	// Add Custom Module Level Variables Here **

	public void InitializeCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Variable Initialization' lines **
		// Begin Wizard Added Variable Initialization

		Object obj = typeof(Ice.UI.App.UD100Entry.UD100Form).InvokeMember("baseDockManager", BindingFlags.Instance | BindingFlags.GetField | BindingFlags.NonPublic, null, UD100Form, null);
        dock =  (Infragistics.Win.UltraWinDock.UltraDockManager)obj;                  
        dock.DockAreas[0].Panes[0].Closed = true;

		this.edvUD100A = ((EpiDataView)(this.oTrans.EpiDataViews["UD100A"]));
		this.edvUD100A.EpiViewNotification += new EpiViewNotification(this.edvUD100A_EpiViewNotification);
		this.UD100A_DataView = this.UD100A_Row.dataView;
		this.UD100A_DataView.ListChanged += new ListChangedEventHandler(this.UD100A_DataView_ListChanged);
		// End Wizard Added Variable Initialization

		// Begin Wizard Added Custom Method Calls

		this.AddLineBtn.Click += new System.EventHandler(this.AddLineBtn_Click);
		this.PrintBtn.Click += new System.EventHandler(this.PrintBtn_Click);
		this.AddPOBtn.Click += new System.EventHandler(this.AddPOBtn_Click);
		// End Wizard Added Custom Method Calls
	}

	public void DestroyCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
		// Begin Wizard Added Object Disposal

		this.AddLineBtn.Click -= new System.EventHandler(this.AddLineBtn_Click);
		this.PrintBtn.Click -= new System.EventHandler(this.PrintBtn_Click);
		this.AddPOBtn.Click -= new System.EventHandler(this.AddPOBtn_Click);
		this.edvUD100A.EpiViewNotification -= new EpiViewNotification(this.edvUD100A_EpiViewNotification);
		this.edvUD100A = null;
		this.UD100A_DataView.ListChanged -= new ListChangedEventHandler(this.UD100A_DataView_ListChanged);
		this.UD100A_DataView = null;
		// End Wizard Added Object Disposal

		// Begin Custom Code Disposal

		// End Custom Code Disposal
	}

	private void AddLineBtn_Click(object sender, System.EventArgs args)
	{
		// ** Place Event Handling Code Here **
		
		//GATHER THE PO LINE DATA
		//Find the Highlighted PONum, POLine, OurQty, PartNum
		EpiDataView POArray = ((EpiDataView)oTrans.EpiDataViews["UD100_PODetail"]);
		EpiDataView UD100PONum = ((EpiDataView)oTrans.EpiDataViews["UD100_PONum"]);

		int PONum = (int)POArray.dataView[POArray.Row]["PONum"];
		int POLine = (int)POArray.dataView[POArray.Row]["POLine"];
		string LineDesc = (string)POArray.dataView[POArray.Row]["LineDesc"];
		decimal OurQty = (decimal)POArray.dataView[POArray.Row]["XOrderQty"];
		string PartNum = (string)POArray.dataView[POArray.Row]["PartNum"];
		string VenPartNum = (string)POArray.dataView[POArray.Row]["VenPartNum"];
		string UOM = (string)POArray.dataView[POArray.Row]["IUM"];
		string Class = (string)POArray.dataView[POArray.Row]["ClassID"];
		string VendorName = (string)UD100PONum.dataView[UD100PONum.Row]["VendorName"];

		

		//APPLY THE DATA TO THE NEW LINE
		//Create a new row for UD100A
		EpiDataView labelsArray = ((EpiDataView)oTrans.EpiDataViews["UD100A"]);
		this.oTrans.GetNewChild();

		//Begin Editing Row
		labelsArray.dataView[labelsArray.Row].BeginEdit();			

		//Set the UD100A Variables to Match Variables Found Above
		labelsArray.dataView[labelsArray.Row]["PONum_c"] = PONum;
		labelsArray.dataView[labelsArray.Row]["POLine_c"] = POLine;
		labelsArray.dataView[labelsArray.Row]["Character01"] = LineDesc;
		labelsArray.dataView[labelsArray.Row]["LabelQty_c"] = Convert.ToInt32(OurQty);
		labelsArray.dataView[labelsArray.Row]["ShortChar01"] = PartNum;
		labelsArray.dataView[labelsArray.Row]["ShortChar02"] = UOM;
		labelsArray.dataView[labelsArray.Row]["ShortChar03"] = Class;
		labelsArray.dataView[labelsArray.Row]["ShortChar04"] = VendorName;
		labelsArray.dataView[labelsArray.Row]["ShortChar05"] = VenPartNum;

		//Complete Editing the Row and Save
		labelsArray.dataView[labelsArray.Row].EndEdit();
		this.oTrans.Update();
		this.oTrans.Refresh();	
	}

	private void AddPOBtn_Click(object sender, System.EventArgs args)
	{
		// ** Place Event Handling Code Here **

		//MessageBox.Show("Test");

		EpiDataView labelsArray = ((EpiDataView)oTrans.EpiDataViews["UD100A"]);
		EpiDataView POArray = ((EpiDataView)oTrans.EpiDataViews["UD100_PODetail"]);
		EpiDataView UD100PONum = ((EpiDataView)oTrans.EpiDataViews["UD100_PONum"]);
		string VendorName = (string)UD100PONum.dataView[UD100PONum.Row]["VendorName"];		

		foreach(DataRow dr in POArray.dataView.Table.Rows) 
		{
			//GATHER THE PO LINE DATA
			//Find the Highlighted PONum, POLine, OurQty, PartNum
			int PONum = (int)dr["PONum"];
			int POLine = (int)dr["POLine"];
			string LineDesc = (string)dr["LineDesc"];
			decimal OurQty = (decimal)dr["XOrderQty"];
			string PartNum = (string)dr["PartNum"];
			string VenPartNum = (string)dr["VenPartNum"];
			string UOM = (string)dr["IUM"];
			string Class = (string)dr["ClassID"];

			//APPLY THE DATA TO THE NEW LINE
			//Create a new row for UD100A
			this.oTrans.GetNewChild();

			//Begin Editing Row
			labelsArray.dataView[labelsArray.Row].BeginEdit();

			//Set the UD100A Variables to Match Variables Found Above
			labelsArray.dataView[labelsArray.Row]["PONum_c"] = PONum;
			labelsArray.dataView[labelsArray.Row]["POLine_c"] = POLine;
			labelsArray.dataView[labelsArray.Row]["Character01"] = LineDesc;
			labelsArray.dataView[labelsArray.Row]["LabelQty_c"] = Convert.ToInt32(OurQty);
			labelsArray.dataView[labelsArray.Row]["ShortChar01"] = PartNum;
			labelsArray.dataView[labelsArray.Row]["ShortChar02"] = UOM;
			labelsArray.dataView[labelsArray.Row]["ShortChar03"] = Class;
			labelsArray.dataView[labelsArray.Row]["ShortChar04"] = VendorName;
			labelsArray.dataView[labelsArray.Row]["ShortChar05"] = VenPartNum;

			//Complete Editing the Row and Save
			labelsArray.dataView[labelsArray.Row].EndEdit();
			this.oTrans.Update();
			this.oTrans.Refresh();			
	
			//MessageBox.Show("Label " + labelsCount.ToString() + " added.");
		}
	}

	private void PrintBtn_Click(object sender, System.EventArgs args)
	//Launch the BAQReport to print the labels
	//Pass a parmater into the BAQReport(A Customization on the BAQReport Form is Required to accept a Parameter)
	{
		// ** Place Event Handling Code Here **

		//Update and save the lines before launching the BAQReport Form
		EpiDataView UD100A_Arr = ((EpiDataView)oTrans.EpiDataViews["UD100A"]);
		this.oTrans.Update();
		this.oTrans.Refresh();

		int Sum = 0;
		foreach(DataRow dr in UD100A_Arr.dataView.Table.Rows)
		{
			Sum = Sum + (int)dr["LabelQty_c"];
		}

		if(Sum > 30) MessageBox.Show("Are you sure you want to print " + Sum.ToString() + " labels?");

		if(UD100A_Arr.Row > -1)
		{

			LaunchFormOptions lfo = new LaunchFormOptions(); 
	
			// ** this is where you would set the parameter to pass to the BAQReport Form
			lfo.ContextValue = UD100A_Arr.dataView[UD100A_Arr.Row]["Key1"];
	
			// ** LBLPRINT would be the MenuID for the BAQReport w/ Customization 					 
			ProcessCaller.LaunchForm(oTrans, "UDLBLRP1", lfo); 
		}	
	}

	private void edvUD100A_EpiViewNotification(EpiDataView view, EpiNotifyArgs args)
	{
		// ** Argument Properties and Uses **
		// view.dataView[args.Row]["FieldName"]
		// args.Row, args.Column, args.Sender, args.NotifyType
		// NotifyType.Initialize, NotifyType.AddRow, NotifyType.DeleteRow, NotifyType.InitLastView, NotifyType.InitAndResetTreeNodes
		
		//Find the rownumber for this new line. args.Row is the row number but it starts at 0 so we add 1 to it. 
		int rowNum = args.Row +1;
		int prevRowNum;

		if ((args.NotifyType == EpiTransaction.NotifyType.AddRow))
		{
			if ((args.Row > -1))
			{
				//If this is the first row save this as row 1.
				if (rowNum == 1)
				{
					view.dataView[view.Row].BeginEdit();
					view.dataView[view.Row]["ChildKey1"] = (rowNum).ToString("000");
					view.dataView[view.Row]["Number01"] = (rowNum);
					view.dataView[view.Row]["LabelQtyPer_c"] = 1;
					
					//Save Data to Row
					view.dataView[view.Row].EndEdit();
					this.oTrans.Update();
					this.oTrans.Refresh();					
				}
				/*If this is not row 1 read the previous row number.  Add 1 to the Previous rownum to get our current rownum.  
				If a row is deleted rownumbers can begin duplicating.  Reading the previous row number prevents duplication.
				*/ 
				else
				{
					prevRowNum = Convert.ToInt32((decimal)view.dataView[args.Row-1]["Number01"]);
					rowNum = prevRowNum + 1;
				
					view.dataView[view.Row].BeginEdit();
					view.dataView[view.Row]["ChildKey1"] = (rowNum).ToString("000");
					view.dataView[view.Row]["Number01"] = (rowNum);
					view.dataView[view.Row]["LabelQtyPer_c"] = 1;
					
					//Save Data to Row
					view.dataView[view.Row].EndEdit();
					this.oTrans.Update();
					this.oTrans.Refresh();
				}			
			}
		}
	}

	private void UD100A_DataView_ListChanged(object sender, ListChangedEventArgs args)
	{
		// ** Argument Properties and Uses **
		// UD100A_DataView[0]["FieldName"]
		// args.ListChangedType, args.NewIndex, args.OldIndex
		// ListChangedType.ItemAdded, ListChangedType.ItemChanged, ListChangedType.ItemDeleted, ListChangedType.ItemMoved, ListChangedType.Reset
		// Add Event Handler Code

		int Sum = 0;
		foreach(DataRow dr in UD100A_DataView.Table.Rows)
		{
			Sum = Sum + (int)dr["LabelQty_c"];
		}

		SumOfLabelsTxt.Text=Sum.ToString();
	}
}

