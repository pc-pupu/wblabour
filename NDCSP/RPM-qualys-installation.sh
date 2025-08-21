#/bin/Bash
######### Qualys Installation for RPM Destro  ##########
echo "Adding Host Enty in /etc/Hosts";
echo "10.248.46.43      qagpublic.ndcad.nic.in" >> /etc/hosts;
echo "Host Entry Done";
sleep 3;
#cd  Qualys Agent Linux;
rpm -ivh qualys-cloud-agent.x86_64.rpm;
echo "RPM Installed";
sudo /usr/local/qualys/cloud-agent/bin/qualys-cloud-agent.sh ActivationId=44aa28ad-33a5-4654-a4ba-ac24aba5ed41 CustomerId=33d72096-431d-6043-83f0-083fb0984774;
echo "Activation Key Added";
echo "Installation completed";
