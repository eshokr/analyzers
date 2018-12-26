// Original Author:  Eslam Shokr
//         Created:  sun, 23 Dec 2018 22:36:50 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include <cmath>

//
// class declaration
//

class DiMuon : public edm::EDAnalyzer {
   public:
      explicit DiMuon(const edm::ParameterSet&);
      ~DiMuon();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  TH1D* histo;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DiMuon::DiMuon(const edm::ParameterSet& iConfig)
{

  edm::Service<TFileService> fs;
    histo = fs->make<TH1D>("Mass" , "mass" , 100 , 0 , 5 );


}


DiMuon::~DiMuon()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DiMuon::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   Handle<reco::TrackCollection> tracks;

 double energy;
double px;
double py;
double pz;
double mass;

iEvent.getByLabel("globalMuons", tracks); 

vector <reco::Track> v;
for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks-> end(); track ++)
{
v.push_back(*track);
}

 
 reco::Track one = v[0];
 reco::Track two = v[1];

  if (tracks->size() == 2)
  {
 
 energy = sqrt(0.106*0.106 + one.p()*one.p()) + sqrt(0.106*0.106 + two.p()*two.p());
        px = one.px() + two.px();
        py = one.py() + two.py();
        pz = one.pz() + two.pz();
        mass = sqrt(energy*energy - px*px - py*py - pz*pz);
        histo ->Fill (mass);
 
 
 
  }
 
  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
DiMuon::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuon::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
DiMuon::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
DiMuon::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
DiMuon::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
DiMuon::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DiMuon::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuon);
