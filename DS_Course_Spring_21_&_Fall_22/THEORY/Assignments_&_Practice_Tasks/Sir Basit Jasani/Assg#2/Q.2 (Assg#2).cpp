#include "String.hpp"
#include "DLL.hpp"

class Widget{
	int ID;
	double cost;
public:
	Widget(double cost=0):cost(cost),ID(counter()){}
	Widget(const Widget& other):cost(other.cost),ID(counter()){}
	
	double get_cost()const{ return cost; }
	
	friend ostream& operator<<(ostream& out,const Widget& self){
		out<<"Widget ID: "<<self.ID<<", Cost: "<<self.cost<<endl;
		return out;
	}
private:
	static int counter(){
		static int count=0;
		return count++;
	}
};

class Data_Record{
	bool status_flag;//i.e. 1-> Shipment received (S) , 0-> Order to be sent (O)
	int quantity;
	String vendor;
public:
	bool success_flag;
	double cost_per_widget;
	
	Data_Record(bool status_flag=true):
		status_flag(status_flag),success_flag(),quantity(0),cost_per_widget(0),vendor(){}
	
	friend ostream& operator<<(ostream& out,const Data_Record& self){
		out<<"Vendor: "<<self.vendor
		   <<", Status: "<<(self.status_flag?"Shipment received":"Order to be sent");
		if(self.status_flag)
			out<<", Cost per widget: "<<self.cost_per_widget;
		else
			out<<", Order Completed: "<<(self.success_flag?"Success":"Failed");
		out<<", Quantity: "<<self.quantity
		   <<", Total Cost: "<<(self.status_flag?self.cost_per_widget*self.quantity:self.cost_per_widget)<<endl;
		return out;
	}
	friend istream& operator>>(istream& in,Data_Record& self){
		in.sync();
		cout<<"Enter Vendor Name:";
		in>>self.vendor;
		cout<<"Enter Quantity:";
		in>>self.quantity;
		if(self.status_flag){
			cout<<"Enter cost per Widget:";
			in>>self.cost_per_widget;
		}
		return in;
	}
	
	bool get_status_flag()const{ return status_flag; }
	int get_quantity()const{ return quantity; }
	const String& get_vendor()const{ return vendor; }
};

int main(){
	//Note: using Queue FIFO order => push_back & pop_front
	DLL<Widget> Widget_Queue;//i.e. warehouse for widget items
	DLL<Data_Record> Order_Record,Shipment_Record;
	
	int choice;
	while (true){
		cout<<"\nENTER YOUR CHOICE: \n"
			<<"1. Add New Widgets To Inventory (from Shipment)\n"
			<<"2. Place Order\n"
			<<"3. View Previous Shipments\n"
			<<"4. View Previous Orders\n"
			<<"5. View Warehouse Items/Widgets\n"
			<<"6. Exit\n=> ";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		switch (choice){
			case 1:{
				Data_Record Shipment_DR;
				cin>>Shipment_DR;
				Widget new_widget(Shipment_DR.cost_per_widget);
				for (int i=0;i<Shipment_DR.get_quantity();++i)
					Widget_Queue.push_back(new_widget);
			#if __cplusplus >= 201103L
				Shipment_Record.push_back(move(Shipment_DR));
			#else
				Shipment_Record.push_back(Shipment_DR);
			#endif
				break;
			}
			case 2:{
				Data_Record Order_DR(false);
				cin>>Order_DR;
				if(Order_DR.get_quantity()>Widget_Queue.size())
					Order_DR.success_flag=false;
				else{
					for (int i=0;i<Order_DR.get_quantity();++i){
						double temp=Widget_Queue.front().get_cost();
						Order_DR.cost_per_widget+=temp;
						Order_DR.cost_per_widget+=(temp/2); //i.e. 50% profit
						Widget_Queue.pop_front();
					}
					Order_DR.success_flag=true;
				}
			#if __cplusplus >= 201103L
				Order_Record.push_back(move(Order_DR));
			#else
				Order_Record.push_back(Order_DR);
			#endif
				break;
			}
			case 3:
				if(Shipment_Record.empty())
					cout<<"No Record Found!"<<endl;
				else
				cout<<Shipment_Record;
				break;
			case 4:
				if(Order_Record.empty())
					cout<<"No Record Found!"<<endl;
				else
					cout<<Order_Record;
				break;
			case 5:
				if(Widget_Queue.empty())
					cout<<"No Record Found!"<<endl;
				else
					cout<<Widget_Queue;
				break;
			case 6:
				return 0;
		}
	}
}

