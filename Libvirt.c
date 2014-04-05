#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{
    virConnectPtr connection;
    virDomainPtr vdp_id, vdp_name;
    int i,ret_val=-1;
    int ch,ch_id,domainnum;
    int *domains;
    char name[25];
    const char *active_name;
    connection = virConnectOpen("xen:///");

    if (connection == NULL) 
    {    fprintf(stderr, "Error opening connection to XEN:///  \n");
        exit(1);
    }
    else
    {
        domainnum=virConnectNumOfDomains(connection);
        domains=malloc(sizeof(int) * domainnum);
        domainnum = virConnectListDomains(connection, domains, domainnum);
    
        printf("\t\t ----Active Domains----  \n");
        for (i = 0 ; i < domainnum ; i++) 
        {
            vdp_id=virDomainLookupByID(connection,i);
            active_name=virDomainGetName(vdp_id);
            printf(" \t\t%s \n", active_name);
         }
         free(domains);

        while(1)
        {
            
           

            printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit\n ");
            printf("Enter Your Choice : ");
            scanf("%d",&ch);

            if(ch != 5)
            {
                    printf("\n Please Insert the Active Domian Name: ");
                    scanf("%s",name);
                    vdp_name = virDomainLookupByName(connection,name);
            }

            switch(ch)
            {
                case 1:
                     
  		               ret_val=virDomainCreate(vdp_name);
                       if(ret_val==0)      
                           printf("Domain %s started\n", name);
                       else
                           printf("Start Operation Failed\n");   
                       break;
                case 2:
                       
		               ret_val=virDomainSuspend(vdp_name);
                       if(ret_val==0)
                           printf("Domain %s Suspended\n", name);
                       else
                           printf("Suspend Operation Failed\n");   
                       break;
                case 3:
                        
		                ret_val=virDomainResume(vdp_name);
                        if(ret_val==0)                     
                            printf("Domain %s Resumed\n", name);
                        else
                            printf("Resume Operation Failed\n");   
                        break;

                case 4: 
                       
		            	ret_val=virDomainShutdown(vdp_name);
                        if(ret_val==0)                     
                            printf("Domain %s Stopped\n", name);
                        else
                            printf("Stop Operation Failed\n");   
                        break;
                case 5: 
                        exit(1);
                default:
                        exit(1);
            }
            
        }
        virConnectClose(connection);
    }
}
